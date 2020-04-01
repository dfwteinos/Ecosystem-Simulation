#include <vector>
#include <map>
#include <string>

using namespace std;

class Plant{
	string	name;					//if it is seeded or seedless
	int		x;						//vertical coordinate
	int		y;						//horizontal coordinate
	char	token;					//first letter of each species name
	int		growthPeriod;
	int		breedingRepPeriod;
  protected:
	int		breedingProb;			//percentage to be in breeding period
	int		illnessProb;			//percentage to be ill
	int		life;
	int		lifeFactor;
  public:
  	Plant(string nam, int position_x, int position_y, char spieces, int breeding, int illness, int life_period, int life_factor);
  	virtual ~Plant(){}

  	string&	get_name();
  	char	get_token();
  	int		get_illnessProb();
  	int		get_breedingProb();
  	void	get_growthPeriod(int& growth);
  	void	get_breedingRepPeriod(int& breeding);
  	void	set_Period(int& growth, int& breeding);
  	virtual int get_size(){}
  	virtual void isIll(bool ill){}
  	virtual void LoseLife(int Count){}
  	bool	isDead();
  	void	get_place(int& i, int& j);			//get plant's coordinates on Terrain
  	virtual void Breeding(char& Token, int i, int j, Plant*& new_plant, int season){}
};

class Seeded : public Plant{
	int		foliage;
	int		seeds;
	int		size;
  public:
  	Seeded(string nam, int position_x, int position_y, char spieces, int breading, int illness, int life_period, int life_factor, int fol, int seed, int Size);
//using default destructor

	int		get_size()/*override*/;
	void	LoseLife(int Count)/*override*/;
	void	isIll(bool ill)/*override*/;
	void	Breeding(char& Token, int i, int j, Plant*& new_plant, int season)/*override*/;
};

class Seedless : public Plant{
  public:
  	Seedless(string nam, int position_x, int position_y, char spieces, int breeding, int illness, int life_period, int life_factor);
//using default destructor

	int		get_size()/*override*/{}
  	void	LoseLife(int Count)/*override*/;
  	void	isIll(bool ill)/*override*/;
  	void	Breeding(char& Token, int i, int j, Plant*& new_plant, int season)/*override*/;
};

class Animal{
	char	token;					//animal species
	string	name;					//name of the animal
	int 	x;						//vertical coordinate
	int 	y;						//horizontal coordinate
	bool	isAlive;
	bool	inHeat;					//if it is in breeding period
	bool	hibernates;				//whether it hibernates or not
	bool	inHibernation;			//whether it is in hibernation or not
	int		growthPeriod;
	int		breedingRepPeriod;
protected:
	bool	isHungry;				//whether it is hungry or not
	int		size;					//size of the animal
	int 	speed;
	int 	eatCount;				//how much the animal eats/per hour
	int 	eatenFood;				//how much it ate
	int		hungerCount;			//days without food
  public:
	Animal(string,char,int,int,int,int,int,bool,bool,int,int,bool,bool,bool);
	virtual ~Animal(){}

	void	Set_Period(int&,int&,bool);
	char	get_token();
	int		get_size();
	int 	get_speed();
	int 	get_HungerDays();
	void	Set_Hunger();
	bool	CheckHunger();
	void	Increase_Hunger();
	void 	get_growthAnimal(int&);
	void 	get_Breeding(int &);
	void 	get_animalName(string&);
	void	setDead();
	bool	get_Alive();
 	virtual void Raise(int,int,int,int,int,int,int,int,int,int){};
	virtual void Raise(int,int,int,int,int,int){};
	virtual void Eat(Plant*& plant){};
	virtual void Eat(int){}
	virtual int  get_attack(){};
	virtual int	 get_defense(){};
};

class Herbivores : public Animal{
	bool	canClimb;
	int		neededFood;

  public:
	Herbivores(string,char,int,int,int,int,int,bool,bool,int,int,int,bool,bool,bool,bool);
//using default destructor

	void Raise(int,int,int,int,int,int)/*override*/;
	void Eat(Plant*& plant)/*override*/;
};

class Carnivores : public Animal {
	int		attack;
	int		defense;
	int		foodNeed;
  public:
	Carnivores(string,int,int,char,int,int,int,int,bool,bool,int,int,bool,bool,bool,int,int);
//using default destructor

	void Raise(int,int,int,int,int,int,int,int,int,int)/*override*/;
	void Eat(int)/*override*/;
	int get_attack()/*override*/;
	int get_defense()/*override*/;
};

class Tile{
	char				environment;		//water(#), hill(^), meadow(")
	Plant				*plant;
	vector <Animal*>	animals;			//array of pointers to Animal
  public:
	Tile(char id);
	~Tile();

	char	get_char();
	Plant*&	get_plant();
	void	set_animal(Animal* animal);		//adds a new animal at the end of vector "animals"
	vector <Animal*>&	get_animals();
	void 	EraseAnimals(int);				//removes "A" animal from vector "animals"
};

class Ecosystem{
	vector <Tile>				temp;
	vector < vector <Tile> >	Terrain;
	int							terrainSize;  	//The size of the Terrain
	int							water;			//number of water tiles
	int							hills;			//number of tiles with hill
	int							meadow;			//number of tiles with meadow
	int							dayOfYear;  	//current day of the simulation
	int							factor;			//growthPeriod, breedingRepPeriod
	vector <int>				n_plants;		//total number of plants and each species of plant
	vector <int>				n_animals;		//total number of animals, herbivores, carnivores and each species of animal
  public:
  	Ecosystem(int size);
//using default destructor

  	void MapGenerator(int lakeSize, int number);	//creating river, lake, hills, meadows and placing plants and animals
  	void GenerateRiver();
  	void GenerateLake(int lakeSize);
  	void GenerateHills(int number);
  	void GenerateMeadow();
  	void PlacePlants();
  	void PlaceAnimals();
  	void RunEcosystem(int days);
  	void ApplySeason(int season);
  	void DailyReset();
 	void CheckDeadEntities();
 	void AnimalMovement();
 	void AnimalEating();
 	void PlantBreeding(int season);
 	void AnimalBreeding(int season);
 	bool FindFreeTile(Plant*& plant, Plant*& new_plant, string& place);
 	void PrintSystem();
 	void PrintPlantStatistics();
 	void PrintAnimalStatistics();
};
