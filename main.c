#include "repo.h"
#include "controller.h"
#include "ui.h"
#include "tests.h"


int main() {
    Repo *repo = createRepo();
    Controller *controller = createController(repo);
    addOfferController(controller, "address 1", "house", 100, 100);
    addOfferController(controller, "address 2", "penthouse", 200, 1000);
    addOfferController(controller, "address 3", "appartament", 40, 50);
    addOfferController(controller, "address 4", "house", 100, 100000);
    addOfferController(controller, "21st of December Boulevard, no 110", "appartament", 60, 170);
    addOfferController(controller, "Bucharest Street, no 60", "house", 90, 90);
    addOfferController(controller, "Teodor Mihali Street, no7", "penthouse", 150, 200);
    addOfferController(controller, "Aurel Vlaicu Street, no 34", "house", 120, 100);
    addOfferController(controller, "Memorandumului Street no 113", "house", 50, 100);
    addOfferController(controller, "Decebal Street", "house", 150, 100);
    UI *ui = createUI(controller);

    startUI(ui);
    destroyUi(ui);

//    tests();
    return 0;
}