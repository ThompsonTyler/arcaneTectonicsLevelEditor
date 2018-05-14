#pragma once
#include <string>
#include <map>

//All structs are components and MUST extend Component struct
struct Component {
public:
	std::string name = "";

	//"Variable Name" : <"Variable Type", "Variable Value">
	std::map<std::string, std::pair<std::string, std::string>> mapping;

	Component() : mapping() {};
	~Component() {};
	Component(std::string n) { name = n; }

	std::string getName() { return name; }
};

struct DumbMovementComponent : public Component {
	DumbMovementComponent() : Component("DumbMovement") {
		const char* val = "movementDistance";
		std::pair<std::string, std::string> pair("int", "1");
		mapping[val] = pair;
	};
	int movementDistance;
};

struct SmartMovementComponent : public Component {
	SmartMovementComponent() : Component("SmartMovement") {
		const char* val = "movementDistance";
		std::pair<std::string, std::string> pair("int", "1");
		mapping[val] = pair;
	};
	int movementDistance;
};

struct ImmobileMovementComponent : public Component {
	ImmobileMovementComponent() : Component("ImmobileMovement") {};
};

struct TeleportMovementComponent : public Component {
	TeleportMovementComponent() : Component("TeleportMovement") {
		const char* val = "movementDistance";
		std::pair<std::string, std::string> pair("int", "1");
		mapping[val] = pair;
	};
	int movementDistance;
};

struct MeleeAttackComponent : public Component {
	MeleeAttackComponent() : Component("MeleeAttack") {};
};

struct RangeOrthoAttackComponent : public Component {
	RangeOrthoAttackComponent() : Component("RangeOrthoAttack") {
		const char* val = "horizontal";
		std::pair<std::string, std::string> pair("bool", "1");
		mapping[val] = pair;

		const char* val2 = "vertical";
		std::pair<std::string, std::string> pair2("bool", "1");
		mapping[val2] = pair2;
	};
	bool horizontal;
	bool vertical;
};

struct RangeDiagAttackComponent : public Component {
	RangeDiagAttackComponent() : Component("RangeDiagAttack") {};
};

struct SplashAttackModComponent : public Component {
	SplashAttackModComponent() : Component("SplashAttackMod") {
		const char* val = "splashArea";
		std::pair<std::string, std::string> pair("int", "1");
		mapping[val] = pair;
	};
	int splashArea;
};

struct DuplicationOnTurnComponent : public Component {
	DuplicationOnTurnComponent() : Component("DuplicationOnTurn") {
		const char* val = "turnsPerDuplicate";
		std::pair<std::string, std::string> pair("int", "1");
		mapping[val] = pair;

		const char* val2 = "numberOfDuplicates";
		std::pair<std::string, std::string> pair2("int", "1");
		mapping[val2] = pair2;
	};
	int turnsPerDuplicate;
	int numberOfDuplicates;
};

struct TileMoveOnTurnComponent : public Component {
	TileMoveOnTurnComponent() : Component("TileMoveOnTurn") {};
};

struct LocationComponent : public Component {
	LocationComponent() : Component("Location") {
		const char* val = "x";
		std::pair<std::string, std::string> pair("int", "1");
		mapping[val] = pair;

		const char* val2 = "y";
		std::pair<std::string, std::string> pair2("int", "1");
		mapping[val2] = pair2;

		const char* val3 = "dir";
		std::pair<std::string, std::string> pair3("int", "1");
		mapping[val3] = pair3;
	};
	int x;
	int y;
	int dir;
};

struct SizeComponent : public Component {
	SizeComponent() : Component("Size") {
		const char* val = "height";
		std::pair<std::string, std::string> pair("int", "1");
		mapping[val] = pair;

		const char* val2 = "width";
		std::pair<std::string, std::string> pair2("int", "1");
		mapping[val2] = pair2;
	};
	int height;
	int width;
};

struct IdleComponent : public Component {
	IdleComponent() : Component("Idle") {
		const char* val = "textureKey";
		std::pair<std::string, std::string> pair("string", "value");
		mapping[val] = pair;
	};
	std::string textureKey;
};

struct NonIdleComponent : public Component {
	NonIdleComponent() : Component("NonIdle") {
		const char* val = "textureLocation";
		std::pair<std::string, std::string> pair("char*", "value");
		mapping[val] = pair;

		const char* val2 = "framesPerSecond";
		std::pair<std::string, std::string> pair2("int", "1");
		mapping[val2] = pair2;
	};
	char* textureLocation;
	int framesPerSecond;
};

struct ExplodeOnDeathComponent : public Component {
	ExplodeOnDeathComponent() : Component("ExplodeOnDeath") {
		const char* val = "radius";
		std::pair<std::string, std::string> pair("int", "1");
		mapping[val] = pair;

		const char* val2 = "affectTiles";
		std::pair<std::string, std::string> pair2("bool", "1");
		mapping[val2] = pair2;
	};
	int radius;
	bool affectTiles;
};

struct WeaknessResistComponent : public Component {
	WeaknessResistComponent() : Component("WeaknessResist") {
		const char* val = "weaknesses";
		std::pair<std::string, std::string> pair("int*", "1, 1");
		mapping[val] = pair;
	};
	int* weaknesses;
};

struct StrengthResistComponent : public Component {
	StrengthResistComponent() : Component("StrengthResist") {
		const char* val = "strengths";
		std::pair<std::string, std::string> pair("int*", "1, 1");
		mapping[val] = pair;
	};
	int* strengths;
};

struct ImmovablePlayerLimitComponent : public Component {
	ImmovablePlayerLimitComponent() : Component("ImmovablePlayerLimit") {};
};

struct FlyPlayerLimitComponent : public Component {
	FlyPlayerLimitComponent() : Component("FlyPlayerLimit") {};
};

struct RootingComponent : public Component {
	RootingComponent() : Component("Rooting") {};
};