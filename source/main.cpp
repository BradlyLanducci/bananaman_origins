#include <app.h>
#include <layers/game_layer.h>

#include <bananaman_origins.h>
#include <game_ui.h>

//------------------------------------------------------------------//

int main(int argc, char *argv[])
{
    AE::App app;
    app.addLayer<AE::GameLayer>(new BananaManOrigins());
    app.addLayer<AE::GameLayer>(new GameUi());
    return app.run();
}

//------------------------------------------------------------------//
