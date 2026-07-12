#include <app.h>
#include <layers/game_layer.h>

#include <bananaman_origins.h>
#include <game_ui.h>

//------------------------------------------------------------------//

int main(int argc, char *argv[])
{
    AE::App app;

    /*
        I had to make this not as clean :(

        The problem is that layers aren't really setup with how the managers work, so having more than one results in
       all managers being ran twice per loop. Ideally layers should "register" with managers.
    */
    BananaManOrigins *p_game{ new BananaManOrigins() };
    GameUi *p_gameUi{ new GameUi() };
    p_game->setUi(p_gameUi);

    app.addLayer<AE::GameLayer>(p_game);

    return app.run();
}

//------------------------------------------------------------------//
