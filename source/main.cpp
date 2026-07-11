#include <app.h>
#include <layers/game_layer.h>

#include <scenes/level_1.h>

//------------------------------------------------------------------//

int main(int argc, char *argv[])
{
    AE::App app;
    app.addLayer<AE::GameLayer>(new Level1());
    return app.run();
}

//------------------------------------------------------------------//