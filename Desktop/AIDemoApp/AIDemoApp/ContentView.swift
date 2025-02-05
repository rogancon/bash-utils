import SwiftUI
import CoreData

// Модель данных для сообщения
struct Message: Identifiable, Codable {
    let id: UUID
    let content: String
    let isUser: Bool
    let timestamp: Date

    init(id: UUID = UUID(), content: String, isUser: Bool, timestamp: Date = Date()) {
        self.id = id
        self.content = content
        self.isUser = isUser
        self.timestamp = timestamp
    }
}

// Настройки пользователя
class UserSettings: ObservableObject {
    @Published var isDarkMode: Bool {
        didSet {
            UserDefaults.standard.set(isDarkMode, forKey: "isDarkMode")
        }
    }
    @Published var fontSize: CGFloat {
        didSet {
            UserDefaults.standard.set(fontSize, forKey: "fontSize")
        }
    }
    @Published var accentColor: Color {
        didSet {
            if let colorInt = accentColor.toInt() {
                UserDefaults.standard.set(colorInt, forKey: "accentColor")
            }
        }
    }

    init() {
        self.isDarkMode = UserDefaults.standard.bool(forKey: "isDarkMode")
        self.fontSize = UserDefaults.standard.object(forKey: "fontSize") as? CGFloat ?? 16
        let colorInt = UserDefaults.standard.integer(forKey: "accentColor")
        self.accentColor = Color(colorInt)
    }
}

// Расширение для работы с Color
extension Color {
    func toInt() -> Int? {
        let uiColor = UIColor(self)
        var red: CGFloat = 0
        var green: CGFloat = 0
        var blue: CGFloat = 0
        var alpha: CGFloat = 0
        uiColor.getRed(&red, green: &green, blue: &blue, alpha: &alpha)

        let redInt = Int(red * 255)
        let greenInt = Int(green * 255)
        let blueInt = Int(blue * 255)

        return (redInt << 16) + (greenInt << 8) + blueInt
    }

    init(_ int: Int) {
        let red = CGFloat((int >> 16) & 0xFF) / 255
        let green = CGFloat((int >> 8) & 0xFF) / 255
        let blue = CGFloat(int & 0xFF) / 255
        self.init(red: red, green: green, blue: blue)
    }
}

// Модель данных для чата
class AIViewModel: ObservableObject {
    @Published var userInput: String = ""
    @Published var messages: [Message] = []
    @Published var isLoading: Bool = false

    private let persistenceController = PersistenceController.shared

    init() {
        loadMessages()
    }

    func sendMessage() {
        guard !userInput.trimmingCharacters(in: .whitespaces).isEmpty else { return }

        let userMessage = Message(content: userInput, isUser: true)
        messages.append(userMessage)
        saveMessage(userMessage)

        let userInputCopy = userInput
        userInput = ""
        isLoading = true

        DispatchQueue.main.asyncAfter(deadline: .now() + 2.0) {
            let aiResponse = Message(content: "Это тестовый ответ от ИИ на ваше сообщение: \(userInputCopy)", isUser: false)
            self.messages.append(aiResponse)
            self.saveMessage(aiResponse)
            self.isLoading = false
        }
    }

    private func loadMessages() {
        let request: NSFetchRequest<MessageEntity> = MessageEntity.fetchRequest()
        request.sortDescriptors = [NSSortDescriptor(keyPath: \MessageEntity.timestamp, ascending: true)]

        do {
            let messageEntities = try persistenceController.container.viewContext.fetch(request)
            messages = messageEntities.compactMap { entity in
                guard let content = entity.content, let timestamp = entity.timestamp else { return nil }
                return Message(id: entity.id ?? UUID(), content: content, isUser: entity.isUser, timestamp: timestamp)
            }
        } catch {
            print("Error loading messages: \(error)")
        }
    }

    private func saveMessage(_ message: Message) {
        let context = persistenceController.container.viewContext
        let entity = MessageEntity(context: context)
        entity.id = message.id
        entity.content = message.content
        entity.isUser = message.isUser
        entity.timestamp = message.timestamp

        do {
            try context.save()
        } catch {
            print("Error saving message: \(error)")
        }
    }
}


// Приветственный экран
struct BallOfThoughtsView: View {
    @State private var animate = false

    var body: some View {
        NavigationView {
            ZStack {
                LinearGradient(
                    gradient: Gradient(colors: [Color.orange.opacity(0.5), Color.pink.opacity(0.6)]),
                    startPoint: .topLeading,
                    endPoint: .bottomTrailing
                )
                .ignoresSafeArea()

                VStack(spacing: 20) {
                    Text("Клубок")
                        .font(.system(size: 40, weight: .bold, design: .rounded))
                        .foregroundColor(.white)

                    Text("Твой дневник мыслей с ИИ")
                        .font(.headline)
                        .foregroundColor(.white.opacity(0.8))
                        .multilineTextAlignment(.center)

                    Spacer()

                    ZStack {
                        ForEach(0..<12, id: \.self) { index in
                            Circle()
                                .stroke(lineWidth: 2)
                                .foregroundColor(.white.opacity(0.5))
                                .frame(width: CGFloat(100 + index * 10), height: CGFloat(100 + index * 10))
                                .offset(x: animate ? CGFloat.random(in: -20...20) : 0, y: animate ? CGFloat.random(in: -20...20) : 0)
                                .animation(Animation.easeInOut(duration: 2).repeatForever(autoreverses: true))
                        }
                    }
                    .frame(width: 200, height: 200)
                    .onAppear {
                        animate = true
                    }

                    Spacer()

                    NavigationLink(destination: MainView()) {
                        Text("Начать")
                            .font(.headline)
                            .foregroundColor(.white)
                            .padding()
                            .frame(maxWidth: .infinity)
                            .background(Color.blue)
                            .cornerRadius(15)
                            .shadow(color: Color.black.opacity(0.2), radius: 5, x: 0, y: 5)
                    }
                    .padding(.horizontal)
                }
                .padding()
            }
            .navigationBarHidden(true)
        }
    }
}

// Главный интерфейс приложения с вкладками
struct MainView: View {
    var body: some View {
        TabView {
            ContentView()
                .tabItem {
                    Label("Чат", systemImage: "message.fill")
                }

            HistoryView()
                .tabItem {
                    Label("История", systemImage: "clock.fill")
                }

            SettingsView()
                .tabItem {
                    Label("Настройки", systemImage: "gearshape.fill")
                }
        }
    }
}

// Чат вкладка
struct ContentView: View {
    @StateObject private var viewModel = AIViewModel()
    @EnvironmentObject var settings: UserSettings

    var body: some View {
        ZStack {
            LinearGradient(
                gradient: Gradient(colors: [settings.accentColor.opacity(0.3), settings.accentColor.opacity(0.5)]),
                startPoint: .topLeading,
                endPoint: .bottomTrailing
            )
            .edgesIgnoringSafeArea(.all)

            VStack(spacing: 0) {
                ScrollViewReader { proxy in
                    ScrollView {
                        LazyVStack(spacing: 12) {
                            ForEach(viewModel.messages) { message in
                                ChatBubble(message: message)
                                    .id(message.id)
                            }
                        }
                        .padding(.vertical)
                    }
                    .onChange(of: viewModel.messages.count) { _ in
                        if let lastMessage = viewModel.messages.last {
                            withAnimation {
                                proxy.scrollTo(lastMessage.id, anchor: .bottom)
                            }
                        }
                    }
                }

                VStack(spacing: 12) {
                    HStack {
                        TextField("Введите сообщение...", text: $viewModel.userInput)
                            .padding()
                            .background(Color.white.opacity(0.9))
                            .cornerRadius(25)

                        Button(action: viewModel.sendMessage) {
                            Image(systemName: "arrow.up.circle.fill")
                                .font(.system(size: 32))
                                .foregroundColor(settings.accentColor)
                        }
                    }
                    .padding()
                    .background(Color.white.opacity(0.1))
                }
            }

            if viewModel.isLoading {
                ProgressView()
                    .progressViewStyle(CircularProgressViewStyle())
                    .scaleEffect(1.5)
                    .frame(maxWidth: .infinity, maxHeight: .infinity)
                    .background(Color.black.opacity(0.4))
            }
        }
    }
}

// История вкладка
struct HistoryView: View {
    @Environment(\.managedObjectContext) private var viewContext
    @FetchRequest(
        sortDescriptors: [NSSortDescriptor(keyPath: \MessageEntity.timestamp, ascending: true)],
        animation: .default
    )
    private var messages: FetchedResults<MessageEntity>

    var body: some View {
        NavigationView {
            ZStack {
                LinearGradient(
                    gradient: Gradient(colors: [Color.orange.opacity(0.3), Color.red.opacity(0.5)]),
                    startPoint: .topLeading,
                    endPoint: .bottomTrailing
                )
                .ignoresSafeArea()

                VStack {
                    Text("История запросов")
                        .font(.system(size: 32, weight: .bold, design: .rounded))
                        .foregroundColor(.black)
                        .padding()

                    if messages.isEmpty {
                        Spacer()
                        Text("Здесь будет отображаться история ваших запросов.")
                            .foregroundColor(.gray)
                        Spacer()
                    } else {
                        List {
                            ForEach(messages, id: \.self) { message in
                                VStack(alignment: .leading) {
                                    Text(message.content ?? "Без текста")
                                        .font(.headline)
                                    Text(message.timestamp ?? Date(), style: .date)
                                        .font(.caption)
                                        .foregroundColor(.gray)
                                }
                                .padding(.vertical, 4)
                            }
                        }
                    }
                }
            }
        }
    }
}

// Настройки вкладка
struct SettingsView: View {
    var body: some View {
        ZStack {
            LinearGradient(
                gradient: Gradient(colors: [Color.green.opacity(0.3), Color.blue.opacity(0.5)]),
                startPoint: .topLeading,
                endPoint: .bottomTrailing
            )
            .ignoresSafeArea()

            VStack {
                Text("Настройки")
                    .font(.system(size: 32, weight: .bold, design: .rounded))
                    .foregroundColor(.black)
                    .padding()

                Spacer()

                Text("Здесь можно изменить настройки приложения.")
                    .foregroundColor(.gray)

                Spacer()
            }
        }
    }
}

// Компонент сообщений
struct ChatBubble: View {
    let message: Message
    @EnvironmentObject var settings: UserSettings

    var body: some View {
        HStack {
            if message.isUser { Spacer() }

            Text(message.content)
                .padding()
                .background(message.isUser ? settings.accentColor : Color.gray.opacity(0.2))
                .foregroundColor(message.isUser ? .white : .primary)
                .cornerRadius(20)
                .font(.system(size: settings.fontSize))

            if !message.isUser { Spacer() }
        }
        .padding(.horizontal)
    }
}

