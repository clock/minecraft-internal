#include "mappings.hpp"

// 1.8.9 mappings for lunar client

void init_mappings() {
	// minecraft class
	klass minecraft_class;
	minecraft_class.class_name = "net.minecraft.client.Minecraft";
	minecraft_class.methods["get_minecraft"] = { "getMinecraft", "()Lnet/minecraft/client/Minecraft;" };
	minecraft_class.fields["get_player"] = { "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;" };
	minecraft_class.fields["get_world"] = { "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;" };

	// world class
	klass world_class;
	world_class.class_name = "net.minecraft.world.World";
	world_class.fields["player_list"] = { "playerEntities", "Ljava/util/List;" };

	// entity class
	klass entity_class;
	entity_class.class_name = "net.minecraft.entity.Entity";
	
	// x, y, z
	entity_class.fields["x"] = { "posX", "D" };
	entity_class.fields["y"] = { "posY", "D" };
	entity_class.fields["z"] = { "posZ", "D" };

	// death
	entity_class.fields["death"] = { "isDead", "Z" };

	// yaw, pitch
	entity_class.fields["yaw"] = { "rotationYaw", "F" };
	entity_class.fields["pitch"] = { "rotationPitch", "F" };

	// entity id
	entity_class.methods["id"] = { "getEntityId", "()I" };

	// add to mappings
	mappings["minecraft"] = minecraft_class;
	mappings["world"] = world_class;
	mappings["entity"] = entity_class;
}