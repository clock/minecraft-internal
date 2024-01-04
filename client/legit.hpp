#pragma once
#include "c_entity.hpp"
#include "c_world.hpp"

namespace Legit {
	void run(std::shared_ptr<c_entity> local_player, std::unique_ptr<c_world> world);
}