#include "legit.hpp"

void Legit::run(std::shared_ptr<c_entity> local_player, std::unique_ptr<c_world> world) {
	
	auto players = world->get_players();

	int i = 0;

	for (auto player : players) {

		printf("player %d: ", i++);
		// x, y, z
		double x = player->get_x();
		double y = player->get_y();
		double z = player->get_z();

		printf("%f/%f/%f\n\n", x, y, z);

	}

}