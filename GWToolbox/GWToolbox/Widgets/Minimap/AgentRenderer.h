#pragma once

#include <vector>

#include <GWCA\GameEntities\Agent.h>

#include "Color.h"
#include "VBuffer.h"

class AgentRenderer : public VBuffer {
public:
	AgentRenderer();

	void Render(IDirect3DDevice9* device) override;

	void DrawSettings();
	void LoadSettings(CSimpleIni* ini, const char* section);
	void SaveSettings(CSimpleIni* ini, const char* section) const;

private:
	static const size_t shape_size = 4;
	enum Shape_e { Tear, Circle, Quad, BigCircle };
	enum Color_Modifier { 
		None, // rgb 0,0,0
		Dark, // user defined
		Light, // user defined
		CircleCenter // alpha -50
	};
	struct Shape_Vertex : public GW::Vector2f {
		Shape_Vertex(float x, float y, Color_Modifier mod) 
			: GW::Vector2f(x, y), modifier(mod) {}
		Color_Modifier modifier;
	};
	struct Shape_t {
		std::vector<Shape_Vertex> vertices;
		void AddVertex(float x, float y, Color_Modifier mod);
	};
	Shape_t shapes[shape_size];

	void Initialize(IDirect3DDevice9* device) override;

	void Enqueue(GW::Agent* agent);
	Color GetColor(GW::Agent* agent) const;
	float GetSize(GW::Agent* agent) const;
	Shape_e GetShape(GW::Agent* agent) const;

	void Enqueue(Shape_e shape, GW::Agent* agent, float size, Color color);

	D3DVertex* vertices;		// vertices array
	unsigned int vertices_count;// count of vertices
	unsigned int vertices_max;	// max number of vertices to draw in one call
	unsigned int max_shape_verts;// max number of triangles in a single shape

	Color color_agent_modifier;
	Color color_eoe;
	Color color_qz;
	Color color_target;
	Color color_player;
	Color color_player_dead;
	Color color_signpost;
	Color color_item;
	Color color_hostile;
	Color color_hostile_damaged;
	Color color_hostile_dead;
	Color color_neutral;
	Color color_ally;
	Color color_ally_npc;
	Color color_ally_spirit;
	Color color_ally_minion;
	Color color_ally_dead;

	float size_default;
	float size_player;
	float size_signpost;
	float size_item;
	float size_boss;
	float size_minion;
};
