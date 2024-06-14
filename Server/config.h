#ifndef CONFIG_H
#define CONFIG_H

/* Window Value */
#define GAME_NAME "Pokemon"
constexpr int GAME_WIDTH = 1280;
constexpr int GAME_HEIGHT = 720;

/* Game Value */
constexpr int MAX_LV = 15;
constexpr int INIT_ATK = 20;
constexpr int INIT_DEF = 10;
constexpr int INIT_HP = 100;
constexpr int INIT_SPEED = 2;

constexpr int INC = 1;
constexpr int ALL_POKEMON_CNT = 8;

/* Json Type */
constexpr int LOGIN = 0;
constexpr int LOGIN_SUCCEED = 10;
constexpr int LOGIN_FAILED = 20;
constexpr int REGIST = 1;
constexpr int REGIST_SUCCEED = 11;
constexpr int REGIST_FAILED = 21;
constexpr int CHECK_POKEMON_AND_USER_INFO = 2;
constexpr int POKEMON_INFO = 3;
constexpr int CHECK_NO_POKEMON = 31;
constexpr int BAG = 4;
constexpr int RANK = 5;
constexpr int BATTLE_LIST = 6;
constexpr int CHOSE = 61;
constexpr int LV_UP_BATTLE = 62;
constexpr int FIGHT_BATTLE = 63;
constexpr int ABANDON = 7;
constexpr int ABANDON_CONFIRM = 71;
constexpr int LOGOUT = 8;

#endif // CONFIG_H
