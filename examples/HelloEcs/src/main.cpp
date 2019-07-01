#include <iostream>
#include <ecs/ecs.hpp>


struct vec2
{
    float x{.0f};
    float y{.0f};
};

struct name
{
    std::string val{""};
};

void nameSystem() {
    for(auto & v:ecs::get<name>()) {
        std::cout   << "\tname says : "
                    << "entity " << v.entityID << " -> "
                    << v.val << '\n';
    }
}

void vectorSystem() {
    for(auto & v:ecs::get<vec2>()) {
        std::cout   << "\tvec2 says : "
                    << "entity " << v.entityID << " -> "
                    << v.x << ':' << v.y << '\n';
    }
}

int main() {
	std::cout   << "Hello ECS\n"
	            << "This program will perform simple tests for the\n"
                << "current Entity Component System\n";

    std::cout   << "\nStarting tests\n"
	            << "Generate entity & bind two components... \n";

    ecs::index_t e{ecs::create()};              assert(ecs::entity::exist(e));
    ecs::attach<vec2>(e, 8.9f, 7.21f);          assert(ecs::component::exist<vec2>(e));
    ecs::attach<name>(e, "basic ecs");          assert(ecs::component::exist<name>(e));

    assert(!ecs::empty(e));

    std::cout   << "\tcomponent signature : "
                << ecs::entity::getSignature(e) << '\n'
                << "\nstarting systems... \n";

    nameSystem();
    vectorSystem();

    std::cout   << "systems halted.\n";


    std::cout   << "\nremoving the first component... \n";
    ecs::detach<vec2>(e);
    assert(ecs::entity::exist(e) & !ecs::component::exist<vec2>(e));

    std::cout   << "\tcomponent signature : "
                << ecs::entity::getSignature(e) << '\n';

    std::cout   << "\nremoving entity... \n";
    ecs::remove(e);
    assert(!ecs::entity::exist(e));
    //TODO: assert all components are removed


    std::cout   << "\ntesting sequence done.\n";
	
	
	return 0;
}