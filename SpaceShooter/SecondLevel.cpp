
void Level::secondLevel()
{
    
    vector<Upgrade *> upgrades = vector<Upgrade *>();
    
    Player *player = new Player(511, 742, 58, 64, false, 1, 10, upgrades, "player");
    Enemy *bEnemy1 = new BasicAlien(382, 9, "enemy1");
    Enemy *sEnemy6 = new StrongerAlien(382, 72, "enemy2");
    Enemy *bEnemy2 = new BasicAlien(445, 9, "enemy1");
    Enemy *sEnemy7 = new StrongerAlien(445, 72, "enemy2");
    Enemy *bEnemy3 = new BasicAlien(508, 9, "enemy1");
    Enemy *sEnemy8 = new StrongerAlien(508, 72, "enemy2");
    Enemy *bEnemy4 = new BasicAlien(571, 9, "enemy1");
    Enemy *sEnemy9 = new StrongerAlien(571, 72, "enemy2");
    Enemy *bEnemy5 = new BasicAlien(634, 9, "enemy1");
    Enemy *sEnemy10 = new StrongerAlien(634, 72, "enemy2");
    Upgrade *shield1 = new Upgrade(295, 50, 28, 28, 1, 5000);
    
    players.push_back(player);
    enemies.push_back(bEnemy1);
    enemies.push_back(sEnemy6);
    enemies.push_back(bEnemy2);
    enemies.push_back(sEnemy7);
    enemies.push_back(bEnemy3);
    enemies.push_back(sEnemy8);
    enemies.push_back(bEnemy4);
    enemies.push_back(sEnemy9);
    enemies.push_back(bEnemy5);
    enemies.push_back(sEnemy10);
    po
}

void Level::thirdLevel()
{
    
    vector<Upgrade *> upgrades = vector<Upgrade *>();
    
    Player *player = new Player(511, 742, 58, 64, false, 1, 10, upgrades, "player");
    Enemy *sEnemy1 = new StrongerAlien(382, 9, "enemy2");
    Enemy *sEnemy6 = new StrongerAlien(382, 72, "enemy2");
    Enemy *sEnemy2 = new StrongerAlien(445, 9, "enemy2");
    Enemy *sEnemy7 = new StrongerAlien(445, 72, "enemy2");
    Enemy *sEnemy3 = new StrongerAlien(508, 9, "enemy2");
    Enemy *sEnemy8 = new StrongerAlien(508, 72, "enemy2");
    Enemy *sEnemy4 = new StrongerAlien(571, 9, "enemy2");
    Enemy *sEnemy9 = new StrongerAlien(571, 72, "enemy2");
    Enemy *sEnemy5 = new StrongerAlien(634, 9, "enemy2");
    Enemy *sEnemy10 = new StrongerAlien(634, 72, "enemy2");
    
    players.push_back(player);
    enemies.push_back(sEnemy1);
    enemies.push_back(sEnemy6);
    enemies.push_back(sEnemy2);
    enemies.push_back(sEnemy7);
    enemies.push_back(sEnemy3);
    enemies.push_back(sEnemy8);
    enemies.push_back(sEnemy4);
    enemies.push_back(sEnemy9);
    enemies.push_back(sEnemy5);
    enemies.push_back(sEnemy10);
}

void Level::fourthLevel()
{
    vector<Upgrade *> upgrades = vector<Upgrade *>();
    
    Player *player = new Player(511, 742, 58, 64, false, 1, 10, upgrades, "player");
    Enemy *rpEnemy1 = new RapidFireAlien(450, 9, "enemy3");
    Enemy *rpEnemy2 = new RapidFireAlien(513, 9, "enemy3");
    Enemy *rpEnemy3 = new RapidFireAlien(576, 9, "enemy3");
    Enemy *sEnemy1 = new StrongerAlien(414, 60, "enemy2");
    Enemy *sEnemy2 = new StrongerAlien(477, 60, "enemy2");
    Enemy *sEnemy3 = new StrongerAlien(549, 60, "enemy2");
    Enemy *sEnemy4 = new StrongerAlien(612, 60, "enemy2");
    Enemy *bEnemy1 = new BasicAlien(378, 111, "enemy3");
    Enemy *bEnemy2 = new BasicAlien(450, 111, "enemy3");
    Enemy *bEnemy3 = new BasicAlien(513, 111, "enemy3");
    Enemy *bEnemy4 = new BasicAlien(576, 111, "enemy3");
    Enemy *bEnemy5 = new BasicAlien(639, 111, "enemy3");
    
    players.push_back(player);
    enemies.push_back(bEnemy1);
    enemies.push_back(sEnemy1);
    enemies.push_back(rpEnemy1);
    enemies.push_back(bEnemy2);
    enemies.push_back(sEnemy2);
    enemies.push_back(bEnemy3);
    enemies.push_back(rpEnemy2);
    enemies.push_back(sEnemy3);
    enemies.push_back(bEnemy4);
    enemies.push_back(rpEnemy3);
    enemies.push_back(sEnemy4);
    enemies.push_back(bEnemy5);
}



void Level::bossLevel()
{
    
    vector<Upgrade *> upgrades = vector<Upgrade *>();
    
    Player *player = new Player(511, 742, 58, 64, false, 1, 10, upgrades, "player");
    
    Enemy *boss = new BossAlien(486, 9, "boss");
    
    players.push_back(player);
    enemies.push_back(boss);
}
