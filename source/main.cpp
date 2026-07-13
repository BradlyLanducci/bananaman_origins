#include <app.h>
#include <layers/game_layer.h>

#include <bananaman_origins.h>

//------------------------------------------------------------------//

int main(int argc, char *argv[])
{
    AE::App app;
    app.addLayer<AE::GameLayer>(new BananaManOrigins());

    return app.run();
}

//------------------------------------------------------------------//
