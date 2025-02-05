import SwiftUI

@main
struct BallOfThoughtsApp: App {
    let persistenceController = PersistenceController.shared

    var body: some Scene {
        WindowGroup {
            BallOfThoughtsView()
                .environment(\.managedObjectContext, persistenceController.container.viewContext)
                .environmentObject(UserSettings())
        }
    }
}
