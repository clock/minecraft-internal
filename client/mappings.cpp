#include "mappings.hpp"

// 1.8.9 mappings for lunar client

void init_mappings() {
	/* minecraft class */
	klass minecraft_class;
	minecraft_class.class_name = "net.minecraft.client.Minecraft";

	// get minecraft
	minecraft_class.methods["get_minecraft"] = { "getMinecraft", "()Lnet/minecraft/client/Minecraft;" };

	// get render manager
	minecraft_class.methods["get_render_manager"] = { "getRenderManager", "()Lnet/minecraft/client/renderer/entity/RenderManager;" };

	minecraft_class.fields["get_player"] = { "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;" };
	minecraft_class.fields["get_world"] = { "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;" };

	/* world class */
	klass world_class;
	world_class.class_name = "net.minecraft.world.World";
	world_class.fields["player_list"] = { "playerEntities", "Ljava/util/List;" };

	/* entity class */
	klass entity_class;
	entity_class.class_name = "net.minecraft.entity.Entity";
	
	// hurt time
	entity_class.fields["hurt_time"] = { "hurtResistantTime", "I" };

	// invulnerable
	entity_class.fields["invulnerable"] = { "invulnerable", "Z" };

	// velocity changed
	entity_class.fields["velocity_changed"] = { "velocityChanged", "Z" };

	// motion x, y, z
	entity_class.fields["motion_x"] = { "motionX", "D" };
	entity_class.fields["motion_y"] = { "motionY", "D" };
	entity_class.fields["motion_z"] = { "motionZ", "D" };

	// x, y, z
	entity_class.fields["x"] = { "posX", "D" };
	entity_class.fields["y"] = { "posY", "D" };
	entity_class.fields["z"] = { "posZ", "D" };

	// sneaking
	entity_class.methods["sneaking"] = { "isSneaking", "()Z" };

	// death
	entity_class.fields["death"] = { "isDead", "Z" };

	// yaw, pitch
	entity_class.fields["yaw"] = { "rotationYaw", "F" };
	entity_class.fields["pitch"] = { "rotationPitch", "F" };

	// entity id
	entity_class.methods["id"] = { "getEntityId", "()I" };

	// entity name
	entity_class.methods["name"] = { "getName", "()Ljava/lang/String;" };

	/* active render info */
	klass active_render_info_class;
	active_render_info_class.class_name = "net.minecraft.client.renderer.ActiveRenderInfo";

	// matrix
	active_render_info_class.fields["viewport"] = { "VIEWPORT", "Ljava/nio/IntBuffer;" };
	active_render_info_class.fields["modelview"] = { "MODELVIEW", "Ljava/nio/FloatBuffer;" };
	active_render_info_class.fields["projection"] = { "PROJECTION", "Ljava/nio/FloatBuffer;" };

	/* render manager */
	klass render_manager_class;
	render_manager_class.class_name = "net.minecraft.client.renderer.entity.RenderManager";

	// render pos
	render_manager_class.fields["render_posx"] = { "renderPosX", "D" };
	render_manager_class.fields["render_posy"] = { "renderPosY", "D" };
	render_manager_class.fields["render_posz"] = { "renderPosZ", "D" };

	/* entity living base */
	klass entity_living_base_class;
	entity_living_base_class.class_name = "net.minecraft.entity.EntityLivingBase";

	// health
	entity_living_base_class.methods["health"] = { "getHealth", "()F" };
	entity_living_base_class.methods["max_health"] = { "getMaxHealth", "()F" };

	// add to mappings map
	mappings["minecraft"] = minecraft_class;
	mappings["world"] = world_class;
	mappings["entity"] = entity_class;
	mappings["active_render_info"] = active_render_info_class;
	mappings["render_manager"] = render_manager_class;
	mappings["entity_living_base"] = entity_living_base_class;
}