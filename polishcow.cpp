// sfwtf.cpp: определяет точку входа для приложения.
//

#include "polishcow.h"

using namespace std;


const char* megadataFile = "megadata.cow";
bool isQuitting = false;

void Log(string msg) {
    cout << msg << endl;
}

struct Frame {
    sf::IntRect rect;
    double duration; // in seconds
};

class Animation {
    std::vector<Frame> frames;
    double totalLength;
    double totalProgress;
    sf::Sprite* target;
public:
    Animation(sf::Sprite& target) {
        this->target = &target;
        totalProgress = 0.0;
    }

    void addFrame(Frame&& frame) {
        frames.push_back(std::move(frame));
        totalLength += frame.duration;
    }

    void update(double elapsed) {
        totalProgress += elapsed;
        double progress = totalProgress;
        for (auto& frame : frames) {
            progress -= (frame).duration;
            if (progress <= 0.0 || &(frame) == &frames.back())
            {
                target->setTextureRect((frame).rect);
                if (frame.rect == sf::IntRect(0, 504, 200, 167)) {
                    frames.begin();
                    totalProgress = 0.0f;
                    }
                break; // we found our frame
            }

        }
    }
};

void RendererThread(sf::RenderWindow* window) {
        Log("RenderThread Initializing.");
        window->setActive(true);
        window->setFramerateLimit(15);
        sf::Texture tenor;
        sf::Sprite cow;
        sf::Clock deltaClock;
        sf::Time dt;
        Animation dance(cow);
        if (!tenor.loadFromFile("megadata/tenor.png")) {
            isQuitting = true;
            return;
        }
        cow.setTexture(tenor, true);
        dance.addFrame({sf::IntRect(0, 0, 200, 167), 0.1 }); // 1
        dance.addFrame({ sf::IntRect(603, 336, 200, 167), 0.1 }); // 2
        dance.addFrame({ sf::IntRect(0, 672, 200, 167), 0.1 }); // 3
        dance.addFrame({ sf::IntRect(201, 504, 200, 167), 0.1 }); // 4
        dance.addFrame({ sf::IntRect(201, 672, 200, 167), 0.1 }); // 5
        dance.addFrame({ sf::IntRect(402, 504, 200, 167), 0.1 }); // 6
        dance.addFrame({ sf::IntRect(402, 672, 200, 167), 0.1 }); // 7
        dance.addFrame({ sf::IntRect(603, 504, 200, 167), 0.1 }); // 8
        dance.addFrame({ sf::IntRect(603, 672, 200, 167), 0.1 }); // 9
        dance.addFrame({ sf::IntRect(201, 0, 200, 167), 0.1 }); // 10
        dance.addFrame({ sf::IntRect(0, 168, 200, 167), 0.1 }); // 11
        dance.addFrame({ sf::IntRect(0, 336, 200, 167), 0.1 }); // 12
        dance.addFrame({ sf::IntRect(201, 168, 200, 167), 0.1 }); // 13
        dance.addFrame({ sf::IntRect(201, 336, 200, 167), 0.1 }); // 14
        dance.addFrame({ sf::IntRect(402, 0, 200, 167), 0.1 }); // 15
        dance.addFrame({ sf::IntRect(402, 168, 200, 167), 0.1 }); // 16
        dance.addFrame({ sf::IntRect(603, 0, 200, 167), 0.1 }); // 17
        dance.addFrame({ sf::IntRect(402, 336, 200, 167), 0.1 }); // 18
        dance.addFrame({ sf::IntRect(603, 168, 200, 167), 0.1 }); // 19
        dance.addFrame({ sf::IntRect(0, 504, 200, 167), 0.1 }); // 20
        cow.setPosition(sf::Vector2f(150, 150));
        string wintitle;
        while (!isQuitting) {
            //shape.setOrigin(sf::Vector2f(shape.getScale().x * 2, shape.getScale().y * 2));
            //shape.setRotation(shape.getRotation() + 5.f * dt.asSeconds());
            dance.update(dt.asSeconds());
            window->clear(sf::Color(255,255,255,255));
            window->draw(cow);
            window->display();
            dt = deltaClock.restart();
        }
        window->setActive(false);
        window->close();
        Log("RenderThread finished.");
}

int main()
{
    Log("polishcow.exe is Starting.");
    Log("Made by SergDS in 2020");
    sf::Clock maintimer;
    sf::Text lt;
    sf::Font comic;
    comic.loadFromFile("megadata/comic.ttf");
    lt.setString("Loading...");
    lt.setPosition(sf::Vector2f(200, 200));
    lt.setColor(sf::Color(0, 0, 0, 255));
    lt.setFont(comic);
    sf::RenderWindow window(sf::VideoMode(500, 500), "Polish Cow!");
    sf::Texture mb_tex;
    sf::Sprite mb;
    if (!mb_tex.loadFromFile("megadata/author.png")) {
        isQuitting = true;
        return 1;
    }
    Log("================================");
    Log("This program was made to learn SFML ;)");
    Log("================================");

    mb.setTexture(mb_tex, true);
    mb.setPosition(sf::Vector2f(0, 400));
    window.clear(sf::Color(255, 255, 255, 255));
    window.draw(mb);
    window.draw(lt);
    window.display();
    while (maintimer.getElapsedTime().asSeconds() <= 2) {
        
    }
    sf::Thread rt(&RendererThread, &window);
    window.setActive(false);
    sf::Music cm;
    if (!cm.openFromFile("megadata/music.ogg")) {
        isQuitting = true;
        return 1;
    }
    cm.setLoop(true);
    rt.launch();
    cm.play();
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                cm.stop();
                isQuitting = true;
                rt.wait();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                cm.stop();
                isQuitting = true;
                rt.wait();
            }
        }
        }
    }
    sf::Time quittime = maintimer.getElapsedTime();
    while (maintimer.getElapsedTime().asSeconds() <= quittime.asSeconds() + 0.5) {

    }
    Log("Quitting...");
    return 0;
}