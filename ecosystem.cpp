#include <iostream>
#include <cstdlib>
#include "ecosystem.h"
#include <vector>
#include <string>

using namespace std;
Plant::Plant(string nam, int position_x, int position_y, char spieces, int breeding, int illness, int life_period, int life_factor)
{
	name = nam;
	x = position_x;
	y = position_y;
	token = spieces;
	breedingProb = breeding;
	illnessProb = illness;
	life = life_period;
	lifeFactor = life_factor;
}

string& Plant::get_name()
{
	return name;
}

char Plant::get_token()
{
	return token;
}

int Plant::get_illnessProb()
{
	return illnessProb;
}

int	Plant::get_breedingProb()
{
	return breedingProb;
}

void Plant::get_growthPeriod(int& growth)
{
	growth = growthPeriod;
}

void Plant::get_breedingRepPeriod(int& breeding)
{
	breeding = breedingRepPeriod;
}

void Plant::set_Period(int& growth, int& breeding)
{
	growthPeriod = growth;
	breedingRepPeriod = breeding;
}

bool Plant::isDead()
{
	if(life == 0)
		return true;
	else
		return false;
}

void Plant::get_place(int& i, int& j)				//get plant's coordinates on Terrain
{
	i = x;
	j = y;
}

///////////////////////////////////////////////////////////////////

Seedless::Seedless(string nam, int position_x, int position_y, char spieces, int breeding, int illness, int life_period, int life_factor) : Plant(nam,position_x,position_y,spieces,breeding,illness,life_period,life_factor)
{
}

void Seedless::LoseLife(int Count)
{
	life -= Count;
}

void Seedless::isIll(bool ill)
{
	if(ill == true)
		life -= lifeFactor;
	else
		life += lifeFactor;
}

void Seedless::Breeding(char& Token, int i, int j, Plant*& new_plant, int season)
{
	int growth, breeding;

	if(Token == 'A')												//if it is Algae
		new_plant = new Seedless("Seedless",i,j,'A',25,25,5,2);
	else															//if it is Grass
		new_plant = new Seedless("Seedless",i,j,'G',15,15,5,4);

	if(season == 1)			//Spring
	{
		growth = 5;
		breeding = 10;
	}
	else if(season == 2)	//Summer
	{
		growth = 10;
		breeding = 10;
	}
	else if(season == 3)	//Autumn
	{
		growth = 0;
		breeding = 20;
	}
	else					//Winter
	{
		growth = 10;
		breeding = 0;
	}
	new_plant->set_Period(growth,breeding);
}

//////////////////////////////////////////////////////////////////

Seeded::Seeded(string nam, int position_x, int position_y, char spieces, int breeding, int illness, int life_period, int life_factor, int fol, int seed, int Size) : Plant(nam,position_x,position_y,spieces,breeding,illness,life_period,life_factor)
{
	foliage = fol;
	seeds = seed;
	size = Size;
}

int Seeded::get_size()
{
	return size;
}

void Seeded::LoseLife(int Count)
{
	if(seeds > 0)							//if it has seeds
	{
		seeds -= Count;						//decrease seeds by "Count"
		if(seeds < 0)						//if Count > seeds
		{
			seeds = 0;
			foliage -= (Count - seeds);		//rest of "Count" will be removed from foliage
			if(foliage < 0)
				foliage = 0;
			life -= (Count - seeds);		//if foliage is decreased, so is plant's life
			if(life < 0)
				life = 0;
		}
	}
	else									//if it has no more seeds
	{
		foliage -= Count;					//decrease foliage by "Count"
		if(foliage < 0)
			foliage = 0;
		life -= Count;						//if foliage is decreased, so is plant's life
		if(life < 0)
			life = 0;
	}
}

void Seeded::isIll(bool ill)
{
	if(ill == true)
	{
		foliage -= lifeFactor;
		seeds -= 2*lifeFactor;
		if(foliage == lifeFactor)
			size--;
	}
	else
	{
		foliage += lifeFactor;
		seeds += 2*lifeFactor;
		if(foliage == lifeFactor)
			size++;
	}
}

void Seeded::Breeding(char& Token, int i, int j, Plant*& new_plant, int season)
{
	int growth, breeding;

	if(Token == 'M')														//if it is a Mapple
		new_plant = new Seeded("Seeded",i,j,'M',5,5,20,10,20,10,2);
	else if(Token == 'O')													//if it is an Oak
		new_plant = new Seeded("Seeded",i,j,'O',20,20,30,15,30,15,5);
	else																	//if it is a Pine
		new_plant = new Seeded("Seeded",i,j,'P',15,15,40,20,40,20,5);

	if(season == 1)			//Spring
	{
		growth = 5;
		breeding = 10;
	}
	else if(season == 2)	//Summer
	{
		growth = 10;
		breeding = 10;
	}
	else if(season == 3)	//Autumn
	{
		growth = 0;
		breeding = 20;
	}
	else					//Winter
	{
		growth = 10;
		breeding = 0;
	}
	new_plant->set_Period(growth,breeding);
}

///////////////////////////////////////////////////////////////////

Animal::Animal(string Name,char Token,int Size,int EatenFood,int Speed,int X,int Y,bool IsAlive,bool IsHungry,int HungerCount,int EatCount,bool Hibernates,bool InHibernation,bool InHeat)
{
	token = Token;					//animal species
	name = Name;					//name of the animal
	size = Size;					//size of the animal
	eatCount = EatCount;			//how much the animal eats/per hour
	eatenFood = EatenFood;			//how much it ate
	speed = Speed;					//speed
	x = X;							//vertical coordinate
	y = Y;							//horizontal coordinate
	isHungry = IsHungry;			//whether it is hungry or not
	hungerCount = HungerCount;		//days without food
	hibernates = Hibernates;		//whether it hibernates or not
	inHibernation = InHibernation;	//whether it is in hibernation or not
	inHeat = InHeat;				//if it is in breeding period
	isAlive = IsAlive;				//if it's alive
}

void Animal::Set_Period(int& growth,int& breeding,bool InHibernation)
{
	growthPeriod = growth;
	breedingRepPeriod = breeding;
	inHibernation = InHibernation;
}

void Animal::Set_Hunger()			//set animal as hungry
{
	eatenFood = 0;
	isHungry = true;
}

bool Animal::CheckHunger()
{
	return isHungry;
}

void Animal::Increase_Hunger()
{
	hungerCount++;
	if(hungerCount == 10)			//if it has not eaten in 10 days
		isAlive = false;			//it dies
}

char Animal::get_token()
{
	return token;
}

int Animal::get_size()
{
	return size;
}

int Animal::get_speed()
{
	return speed;
}

int Animal::get_HungerDays()
{
	return hungerCount;
}

void Animal::get_growthAnimal(int& Growth)
{
	Growth = growthPeriod;
}

void Animal::get_Breeding(int& Breeding)
{
	Breeding = breedingRepPeriod;
}

void Animal::get_animalName(string& Name)
{
	Name = name;
}

bool Animal::get_Alive()
{
	return isAlive;
}

void Animal::setDead()
{
	isAlive = false;
}

///////////////////////////////////////////////////////////////////

Herbivores::Herbivores(string Name,char Token,int Size,int Speed,int NeededFood,int X,int Y,bool IsAlive,bool IsHungry,int HungerCount,int EatenFood,int EatCount,bool CanClimb,bool Hibernates,bool InHibernation,bool InHeat) : Animal(Name,Token,Size,EatenFood,Speed,X,Y,IsAlive,IsHungry,HungerCount,EatCount,Hibernates,InHibernation,InHeat), neededFood(NeededFood) , canClimb(CanClimb)
{
//	cout <<"We just created a Herbivor animal!" << endl;
}

void Herbivores::Raise(int Size,int Speed,int NeededFood,int max_Size,int max_Speed,int max_NeededFood)
{	if(size < max_Size)
	{
		size += Size;
		if(size > max_Size)					//in case it overcomes max_Size
			size = max_Size;
	}
	if(speed < max_Speed)
	{
		speed += Speed;
		if(speed > max_Speed)				//in case it overcomes max_Speed
			speed = max_Speed;
	}
	if (neededFood < max_NeededFood)
	{
		neededFood += NeededFood;
		if(neededFood > max_NeededFood)		//in case it overcomes max_NeededFood
			neededFood = max_NeededFood;
	}
}

void Herbivores::Eat(Plant*& plant)
{
	if(eatenFood < neededFood)				//if it has to eat
	{
		eatenFood += eatCount;
		hungerCount = 0;
		if(eatenFood > neededFood)
			eatenFood = neededFood;			//cannot eat more than needed Food
		if(eatenFood == neededFood)
			isHungry = false;
		plant->LoseLife(eatenFood - eatCount);
	}
}

///////////////////////////////////////////////////////////////////

Carnivores::Carnivores(string Name,int FoodNeed,int Size,char Token,int EatenFood,int Speed,int X,int Y,bool IsAlive,bool IsHungry,int HungerCount,int EatCount,bool Hibernates,bool InHibernation,bool InHeat,int Attack,int Defense) : Animal(Name,Token,Size,EatenFood,Speed,X,Y,IsAlive,IsHungry,HungerCount,EatCount,Hibernates,InHibernation,InHeat), attack(Attack), defense(Defense) , foodNeed(FoodNeed)
{
//	cout<<"We just created a Carnivor animal!" << endl;
}

void Carnivores::Raise(int Size,int Attack,int Defense,int Speed,int NeededFood,int max_Size,int max_Attack,int max_Defense,int max_Speed,int max_NeededFood)
{
	if(size < max_Size)
	{
		size += Size;
		if(size > max_Size)					//in case it overcomes max_Size
			size = max_Size;
	}
	if (attack < max_Attack)
	{
		attack += Attack;
		if(attack > max_Attack)				//in case it overcomes max_Attack
			attack = max_Attack;
	}
	if (defense < max_Defense)
	{
		defense += Defense;
		if(defense > max_Defense)			//in case it overcomes max_Defense
			defense = max_Defense;
	}
	if (speed < max_Speed)
	{
		speed += Speed;
		if(speed > max_Speed)				//in case it overcomes max_Speed
			speed = max_Speed;
	}
	if (foodNeed < max_NeededFood)
	{
		foodNeed += NeededFood;
		if(foodNeed > max_NeededFood)		//in case it overcomes max_NeededFood
			foodNeed = max_NeededFood;
	}
}

void Carnivores::Eat(int Size)
{
	eatCount = Size;
	eatenFood += eatCount;
	hungerCount = 0;						//it just ate
	if(eatenFood >= foodNeed)				//if it eats as much or more than it needs
		isHungry = false;					//not hungry any more
}

int Carnivores::get_defense()
{
	return defense;
}

int Carnivores::get_attack()
{
	return attack;
}

///////////////////////////////////////////////////////////////////

Tile::Tile(char id)
{
	environment = id;
	plant = NULL;
}

Tile::~Tile()
{
	delete plant;

	if(animals.size() > 0)
		for(int A=0; A<animals.size(); A++)
			delete animals[A];
}

char Tile::get_char()
{
	return environment;
}

Plant*& Tile::get_plant()
{
	return plant;
}

void Tile::set_animal(Animal* animal)			//adds a new animal at the end of vector "animals"
{
	animals.push_back(animal);
}

vector <Animal*>& Tile::get_animals()
{
	return animals;
}

void Tile::EraseAnimals(int A)					//removes "A" animal from vector "animals"
{
	animals.erase(animals.begin() + A);
}

//////////////////////////////////////////////////////////////////

Ecosystem::Ecosystem(int size)
{
	terrainSize = size;
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
			temp.push_back('0');
		Terrain.push_back(temp);
	}
	water = 0;									//number of water tiles
	hills = 0;									//number of tiles with hill
	meadow = 0;									//number of tiles with meadow
	dayOfYear = 0;								//current day of the simulation
	for(int i=0; i<6; i++)
		n_plants.push_back(0);					//total number of plants and each species of plant (zero at first)
	for(int i=0; i<10; i++)
		n_animals.push_back(0);					//total number of animals, herbivores, carnivores and each species of animal (zero at first)
}

void Ecosystem::GenerateRiver()
{
	int start = rand() %(terrainSize - 9) +5;	//the beggining of the river in the map
	int i=0;
	int chance;
	int route;

	Terrain[i][start-1] = '#';					//the first water tile 
	water++;									//increasing number of water tiles
	for(i=1; i<terrainSize; i++)				//the river crosses all the Terrain
	{
		chance = rand()%10 +1;					//chance from 1 up to 10 
		if(chance <= 3)							//30% chance it will change route
		{
			route = rand() %4 +1;				//from 1 up to 4 (4 possible routes)
			switch(route){
				case(1):						//right by one 
				{
					if(start < terrainSize)		//if we are inside the Terrain
					{
						Terrain[i][start-1] = '#';
						start++;				//will fill first by right tile with water
						water++;				//increasing number of water tiles
					}
					break;
				}
				case(2):						//right by two
				{
					if(start < terrainSize)		//if we are inside the Terrain
					{
						Terrain[i][start-1] = '#';
						start++;				//filling first by right tile with water
						Terrain[i][start-1] = '#';
						water += 2;				//increasing number of water tiles
					}
					if(start < terrainSize)		//if we are inside the Terrain
						start++;				//will fill second by right tile with water
					break;
				}
				case(3):						//left by one
				{
					if(start > 1)				//if we are inside the Terrain
					{
						Terrain[i][start-1] = '#';
						start--;				//will fill first by left tile with water
						water++;				//increasing number of water tiles
					}
					break;
				}
				case(4):						//left by two
				{
					if(start > 1)				//if we are inside the Terrain
					{
						Terrain[i][start-1] = '#';
						start--;				//filling first by left tile with water
						Terrain[i][start-1] = '#';
						water += 2;				//increasing number of water tiles
					}
					if(start > 1)				//if we are inside the Terrain
						start--;				//will fill second by left tile with water
					break;
				}
			}
		}
		Terrain[i][start-1] = '#';				//fill chosen tile with water
		water++;								//increasing number of water tiles
	}
}

void Ecosystem::GenerateLake(int lakeSize)
{
	int x = rand() %(terrainSize);
	int y = rand() %(terrainSize);
	int i;
	int j;

	if(lakeSize == terrainSize)					//if the lake has the size of the Terrain
	{
		for(i=0; i<lakeSize; i++)
			for(j=0; j<lakeSize; j++)
			{
				Terrain[i][j] = '#';			//filling Terrain with water tiles
				water++;						//increasing number of water tiles
			}
	}
	else
	{
		while(x+lakeSize>=terrainSize || y+lakeSize>=terrainSize)	//while we are outside the Terrain
		{
			x=rand() %(terrainSize);
			y=rand() %(terrainSize);
		}

		for(i=x; i<(x+lakeSize); i++)			//lake may overlay a river
			for(j=y; j<(y+lakeSize); j++)
			{
				Terrain[i][j] = '#';
				water++;						//increasing number of water tiles
			}
	}	
}

void Ecosystem::GenerateHills(int number)
{
	int n, size, x, y, i, j, temp_i, temp_j, counter;
	bool flag,flag_out;
	for(n=0; n<number; n++)			//number==the number of the hills that we wanna put
	{
		size = rand() %3 +2;		//Each hill will be from 2 up to 4 at size
		counter = 0;				//Counter stands for the free tiles of the map
		flag = false;
		flag_out=false;
		x = rand() %(terrainSize);	//Random element of variable X
		y = rand() %(terrainSize);	//Random element of variable Y

		for(i=0; i<terrainSize; i++)	//We are checking the Terrain for free positions
			for(j=0; j<terrainSize; j++)
				if(Terrain[i][j].get_char() == '0')
					counter++;		//In the counter variable we are putting the free positions for the hills

		if(counter >= size*size)	//If there is no (more) free space for the hils 
		{
			int odhgos,grammes,odhgos_sthlh,sthles,counter,counter_s;

			for(odhgos_sthlh=0; odhgos_sthlh<terrainSize; odhgos_sthlh++)
			{
				for(odhgos=0; odhgos<terrainSize; odhgos++) //We are visually creating virtual Boxes. Each box has the proper size of the hill we wanna search if we can put, each time
				{
					counter=0;
					for(grammes=odhgos; grammes<=(odhgos+size-1); grammes++)
					{
						for(sthles=odhgos_sthlh; sthles<=(odhgos_sthlh+size-1); sthles++)		//We are checking one by one the columns
						{
							if( (sthles+1)>terrainSize || (grammes+1)>terrainSize )				//If we are going to go out of the Terrain, and we don't want that :) 
								counter=0;
							else
							{
								if(Terrain[grammes][sthles].get_char()!= '#' && Terrain[grammes][sthles].get_char()!= '^') 	//We are checking just for water and hills,beacuse we don't have any meadow yet
									counter++;																				
							}
						}
					}
					if(counter==size*size && flag_out==false)
						flag_out=true;
				}
			}
			if(flag_out != true)
				cout<<"Not enough Space for Hill,size: " << size <<endl;
									//If we are here we know that the if is true
			counter = 0;			//We are doing the counter zero
			while(flag == false && counter<terrainSize*terrainSize && flag_out==true)		//We are checking the whole terrain
			{
				while((Terrain[x][y].get_char() =='^' || Terrain[x][y].get_char() == '#' || x+size > terrainSize || y+size > terrainSize)) // && counter < terrainSize*terrainSize)														
				{
					x = rand() %(terrainSize);		//Random variable x
					y = rand() %(terrainSize);		//Random variable y
				}						
				counter = 0;			
				i=x;					
				while(i < ( x+size ) && flag == false)													
				{
					j=y;								
					while(j < ( y+size ) && flag == false)		
					{
						if(Terrain[i][j].get_char() == '#' || Terrain[i][j].get_char() == '^' )		//We are checking if inside the box we wanna create there is some water or some hill already
						{
							temp_i = i;
							temp_j = j;
							flag = true;							//Flag will be true only when inside our virtual box there will be someone 
						}											
						j++;
					}
					i++;
				}
				if(flag == true)		//Flag will be true only when inside our virtual box there will be someone
				{
					x = temp_i;			//X==the place where something went wrong
					y = temp_j;			//Y==the place where something went wrong
					flag = false;
				}
				else
				{						//If we found the free box and everything is OK!
					for(i=x; i<(x+size); i++)								
						for(j=y; j<(y+size); j++) 						
						{
							Terrain[i][j] = '^';				//We are creating the hill-box
							hills++;							//increasing number of tiles with hills
						}
					flag = true;										
				}
				counter++;												
			}
		}
		else							//When there is no free boxes for the hill we wanna create
		{
			cout << "Not enough space for more hills.\n";
			n = number;
			break;
		}
	}
}

void Ecosystem::GenerateMeadow()
{
	int i, j;
	for(i=0; i<terrainSize; i++)
		for(j=0; j<terrainSize; j++)
			if(Terrain[i][j].get_char() == '0')			//if it is not a water tile or hill
			{
				Terrain[i][j] = '"';
				meadow++;								//increasing number of tiles with meadow
			}
}

void Ecosystem::MapGenerator(int lakeSize, int number)	//creating river, lake, hills, meadows and placing plants and animals
{
	GenerateRiver();
	GenerateLake(lakeSize);
	GenerateHills(number);
	GenerateMeadow();
	PlacePlants();
	PlaceAnimals();
}

void Ecosystem::PlacePlants()
{
	int spieces, new_plant;			//spieces: randomly choose which spieces will be created, new_plant: randomly choose whether a plant will be created or not
	int n_g, n_a, n_m, n_o, n_p;	//maximum number of each species that can be created
	int g=0, a=0, m=0, o=0, p=0;	//actual number of each species that will be created

	n_a = rand() %(water+1);		//from 0 up to water
	n_m = rand() %(hills+1);		//from 0 up to hills
	n_p = hills - n_m;				//(n_m + n_p) = hills
	n_g = rand() %(meadow+1);		//from 0 up to meadow
	n_o = meadow - n_g - n_m;		//(n_m + n_g + n_o) = meadow
	if(n_o < 0)
		n_o = 0;

	for(int i=0; i<terrainSize; i++)
	{
		for(int j=0; j<terrainSize; j++)
		{
			new_plant = rand() %2;							//either 0 or 1
			if(new_plant == 1)								//if 1, a new plant will be created
			{
				if(Terrain[i][j].get_char() == '#')			//River or Lake ('#')
				{
					if(a < n_a)								//if more Algae can be created
					{
						Terrain[i][j].get_plant() = new Seedless("Seedless",i,j,'A',25,25,5,2);
						a++;								//increasing number of Algae created
					}
					else
						Terrain[i][j].get_plant() = NULL;
				}
				else if(Terrain[i][j].get_char() == '^')	//Hill ('^')
				{
					spieces = rand()%2 +1;					//if 1: Maple will be created, else: Pine will be created
					if(spieces == 1)						//Maple
					{
						if(m < n_m)							//if more Maples can be created
						{
							Terrain[i][j].get_plant() = new Seeded("Seeded",i,j,'M',5,5,20,10,20,10,2);
							m++;							//increasing number of Maples created
						}
						else
							Terrain[i][j].get_plant() = NULL;
					}
					else									//Pine
					{
						if(p < n_p)							//if more Pines can be created
						{
							Terrain[i][j].get_plant() = new Seeded("Seeded",i,j,'P',15,15,40,20,40,20,5);
							p++;							//increasing number of Pines created
						}
						else
							Terrain[i][j].get_plant() = NULL;
					}
				}
				else										//Meadow ('"')
				{
					spieces = rand()%3 +1;					//if 1: Grass will be created, else if 2: Maple will be created, else: Oak will be created
					if(spieces == 1)						//Grass
					{
						if(g < n_g)							//if more Grass can be created
						{
							Terrain[i][j].get_plant() = new Seedless("Seedless",i,j,'G',15,15,5,4);
							g++;							//increasing number of grass created
						}
						else
							Terrain[i][j].get_plant() = NULL;
					}
					else if(spieces == 2)					//Maple
					{
						if(m < n_m)							//if more Maples can be created
						{
							Terrain[i][j].get_plant() = new Seeded("Seeded",i,j,'M',5,5,20,10,20,10,2);
							m++;							//increasing number of Maples created
						}
						else
							Terrain[i][j].get_plant() = NULL;
					}
					else									//Oak
					{
						if(o < n_o)							//if more Oaks can be created
						{
							Terrain[i][j].get_plant() = new Seeded("Seeded",i,j,'O',20,20,30,15,30,15,5);
							o++;							//increasing number of Oaks created
						}
						else
							Terrain[i][j].get_plant() = NULL;
					}
				}
			}
			else											//if new_plant = 0: no plants will be created in this tile
				Terrain[i][j].get_plant() = NULL;
		}
	}
	n_plants[0] = a + m + p + g + o;						//increasing total number of plants
	n_plants[1] = a;										//increasing total number of Algae
	n_plants[2] = m;										//increasing total number of Maples
	n_plants[3] = p;										//increasing total number of Pines
	n_plants[4] = g;										//increasing total number of Grass
	n_plants[5] = o;										//increasing total number of Oaks
}

void Ecosystem::PlaceAnimals()
{
	enum Animals{bear , wolf , fox , salmon , groundhog , rabbit , deer};
	vector <int> animal_counter;					//array with number of each spieces of animals to be created
	int	number, Counter,r,i,j;
	for(int A=bear; A<=deer; A++)
	{
		if(A == bear)
		{
			number = rand() %(hills+1);
			n_animals[2] += number;					//increase total number of carnivores
			n_animals[8] += number;					//increase total number of bears
		}
		else if(A == wolf)
		{
			number = rand() %(hills+meadow+1);
			n_animals[2] += number;					//increase total number of carnivores
			n_animals[9] += number;					//increase total number of wolves
		}
		else if(A == fox)
		{
			number = rand() %(meadow+1);
			n_animals[2] += number;					//increase total number of carnivores
			n_animals[7] += number;					//increase total number of foxes
		}
		else if(A == salmon)
		{
			number = rand() %(water+1);
			n_animals[1] += number;					//increase total number of herbivores
			n_animals[6] += number;					//increase total number of salmons
		}
		else if(A == groundhog)
		{
			number = rand() %(meadow+1);
			n_animals[1] += number;					//increase total number of herbivores
			n_animals[5] += number;					//increase total number of groundhogs
		}
		else if(A == rabbit)
		{
			number = rand() %(meadow+1);
			n_animals[1] += number;					//increase total number of herbivores
			n_animals[4] += number;					//increase total number of rabbits
		}
		else if(A == deer)
		{
			number = rand() %(meadow+1);
			n_animals[1] += number;					//increase total number of herbivores
			n_animals[3] += number;					//increase total number of deers
		}
		animal_counter.push_back(number);
		n_animals[0] += number;						//increase total number of animals
	}

	Counter = animal_counter[wolf];
	for(r=0; r<Counter; r++)						//until "Counter" number of wolves is created
	{
		i = rand() %terrainSize;
		j = rand() %terrainSize;
		while(Terrain[i][j].get_char() == '#')		//wolf does not live in water
		{
			i = rand() %terrainSize;
			j = rand() %terrainSize;
		}
		Terrain[i][j].set_animal(new Carnivores("Wolf",8,7,'C',0,8,i,j,true,true,0,7,false,false,false,8,6));
	}
	Counter = animal_counter[fox];
	for(r=0; r<Counter; r++)						//until "Counter" number of foxes is created
	{
		i = rand() %terrainSize;
		j = rand() %terrainSize;
		while(Terrain[i][j].get_char() != '"')		//fox lives only on meadow
		{
			i = rand() %terrainSize;
			j = rand() %terrainSize;
		}
		Terrain[i][j].set_animal(new Carnivores("Fox",6,4,'C',0,6,i,j,true,true,0,4,false,false,false,5,5));
		}
		Counter = animal_counter[groundhog];
		for(r=0; r<Counter; r++)					//until "Counter" number of groundhogs is created
		{
			i = rand() %terrainSize;
			j = rand() %terrainSize;
			while(Terrain[i][j].get_char() != '"')	//groundhog lives only on meadow
			{
				i = rand() %terrainSize;
				j = rand() %terrainSize;
			}
			Terrain[i][j].set_animal(new Herbivores("Groundhog",'H',3,5,5,i,j,true,true,0,0,1,true,true,false,false));
		}
		Counter = animal_counter[rabbit];
		for(r=0; r<Counter; r++)					//until "Counter" number of rabbits is created
		{
			i = rand() %terrainSize;
			j = rand() %terrainSize;
			while(Terrain[i][j].get_char() != '"')	//rabbit lives only on meadow
			{
				i = rand() %terrainSize;
				j = rand() %terrainSize;
			}
			Terrain[i][j].set_animal(new Herbivores("Rabbit",'H',2,6,4,i,j,true,true,0,0,1,false,false,false,false));
		}
		Counter = animal_counter[deer];
		for(r=0; r<Counter; r++)					//until "Counter" number of deers is created
		{
			i = rand() %terrainSize;
			j = rand() %terrainSize;
			while(Terrain[i][j].get_char() != '"')	//deer only lives on meadow
			{
				i = rand() %terrainSize;
				j = rand() %terrainSize;
			}
			Terrain[i][j].set_animal(new Herbivores("Deer",'H',5,8,8,i,j,true,true,0,0,2,false,false,false,false));
		}
		Counter= animal_counter[salmon];
		for(r=0; r<Counter; r++)					//until "Counter" number of salmons is created
		{
			i = rand() %terrainSize;
			j = rand() %terrainSize;
			while(Terrain[i][j].get_char() != '#')	//salmon only lives in water
			{
				i = rand() %terrainSize;
				j = rand() %terrainSize;
			}
			Terrain[i][j].set_animal(new Herbivores("Salmon",'H',1,5,1,i,j,true,true,0,0,1,false,false,false,false));
		}
}

void Ecosystem::ApplySeason(int season)
{
	Plant*	plant;
	int		plant_growth, plant_breeding,animal_growth,animal_breedingH,animal_breedingC,inHibernation;
	//setting proper factors for plants, herbivores and carnivores on each season
	if(season == 1)				//Spring
	{
		cout << "\nSPRING\n";
		plant_growth = 5;
		plant_breeding = 10;
		animal_growth = 20;
		animal_breedingH = 12;
		animal_breedingC = 11;
		inHibernation = false;
	}
	else if(season == 2)		//Summer
	{
		cout << "\nSUMMER\n";
		plant_growth = 10;
		plant_breeding = 10;
		animal_growth = 30;
		animal_breedingH = 8;
		animal_breedingC = 9;
		inHibernation = false;
	}
	else if(season == 3)		//Autumn
	{
		cout << "\nAUTUMN\n";
		plant_growth = 0;
		plant_breeding = 20;
		animal_growth = 15;
		animal_breedingH = 5;
		animal_breedingC = 9;
		inHibernation = false;
	}
	else if(season == 4)		//Winter
	{
		cout << "\nWINTER\n";
		plant_growth = 10;
		plant_breeding = 0;
		animal_growth = 30;
		animal_breedingH = 18;
		animal_breedingC = 10;
		inHibernation = true;	//only Bears and Groundhogs hibernate, all animals except Bears and Groundhogs have: Animal::hibernates = false
	}

	for(int i=0; i<terrainSize; i++)
	{
		for(int j=0; j<terrainSize; j++)
		{
			plant = Terrain[i][j].get_plant();									//get current plant
			if((plant != NULL) && (plant->isDead() == false))					//if there is an alive plant
				Terrain[i][j].get_plant()->set_Period(plant_growth,plant_breeding);

			if(Terrain[i][j].get_animals().size() > 0)							//if there are animals on current tile
			{
				for(int A=0; A<Terrain[i][j].get_animals().size(); A++)			//until all animlas in vector Tile::animals are checked
				{
					if(Terrain[i][j].get_animals()[A]->get_Alive() == true)		//if current animal is alive
					{
						if(Terrain[i][j].get_animals()[A]->get_token() == 'C')	//if it is a Carnivore
							Terrain[i][j].get_animals()[A]->Set_Period(animal_growth,animal_breedingH,inHibernation);
						else													//if it is a Herbivore
							Terrain[i][j].get_animals()[A]->Set_Period(animal_growth,animal_breedingC,inHibernation);
					}
				}
			}
		}
	}
}

void Ecosystem::DailyReset()
{
	string	animal;
	int		GrowthPeriodP, GrowthPeriodA, ill;
	Plant*	plant;

	dayOfYear++;																		//increasing current day of the simulation

	for(int i=0; i<terrainSize; i++)
	{
		for(int j=0; j<terrainSize; j++)
		{
			plant = Terrain[i][j].get_plant();											//get current plant
			if((plant != NULL) && (plant->isDead() == false))							//if there is an alive plant
			{
				{
					plant->get_growthPeriod(GrowthPeriodP);
					if((GrowthPeriodP != 0) && (dayOfYear%GrowthPeriodP == 0))			//if it is a day of growth for the plants
					{
						ill = rand() %100 +1;											//from 1 up to 100
						if(ill <= plant->get_illnessProb())								//if plant is ill
							plant->isIll(true);
						else															//if plant is not ill
							plant->isIll(false);
					}
				}
			}

			if(Terrain[i][j].get_animals().size() > 0)									//if there are animals on current tile
			{
				for(int A=0; A<Terrain[i][j].get_animals().size(); A++)					//until all animlas in vector Tile::animals are checked
				{
					if(Terrain[i][j].get_animals()[A]->get_Alive() == true)				//if current animal is alive
					{
						Terrain[i][j].get_animals()[A]->Set_Hunger();
						Terrain[i][j].get_animals()[A]->get_growthAnimal(GrowthPeriodA);
						if((dayOfYear%GrowthPeriodA) == 0)								//if it is a day of growth for the animals
						{
							Terrain[i][j].get_animals()[A]->get_animalName(animal);
							if(animal == "Fox")
								Terrain[i][j].get_animals()[A]->Raise(1,1,1,1,1,4,5,5,6,6);
							else if(animal == "Wolf")
								Terrain[i][j].get_animals()[A]->Raise(1,2,2,2,2,7,8,8,8,8);
							else if(animal == "Bear")
								Terrain[i][j].get_animals()[A]->Raise(2,2,2,0,2,10,10,10,4,10);
							else if(animal == "Deer")
								Terrain[i][j].get_animals()[A]->Raise(1,2,2,5,8,8);
							else if(animal == "Rabbit")
								Terrain[i][j].get_animals()[A]->Raise(1,2,1,2,6,4);
							else /*(animal == "Groundhog")*/
								Terrain[i][j].get_animals()[A]->Raise(1,1,1,3,5,5);
						}
					}
				}
			}
		}
	}
}

void Ecosystem::CheckDeadEntities()
{
	int		A;
	Plant	*plant;
	char	token;
	string	name;

	for(int i=0; i<terrainSize; i++)
	{
		for(int j=0; j<terrainSize; j++)
		{
			plant = Terrain[i][j].get_plant();					//get current plant
			if((plant != NULL) && (plant->isDead() == true))	//if plant is dead
			{
				token = plant->get_token();
				delete(plant);									//deleting plant
				Terrain[i][j].get_plant() = NULL;
				n_plants[0]--;									//decreasing total number of plants
				if(token == 'A')								//if it was Algae
					n_plants[1]--;								//decreasing total number of Algae
				else if(token == 'M')							//if it was a Maple
					n_plants[2]--;								//decreasing total number of Maples
				else if(token == 'P')							//if it was a Pine
					n_plants[3]--;								//decreasing total number of Pines
				else if(token == 'G')							//if it was Grass
					n_plants[4]--;								//decreasing total number of Grass
				else if(token == 'O')							//if it was an Oak
					n_plants[5]--;								//decreasing total number of Oaks
			}

			A = 0;												//starting with vector's Tile::animals first animal
			while(Terrain[i][j].get_animals().size() > 0  &&  A < Terrain[i][j].get_animals().size())		//until all animals are checked
			{
				if(Terrain[i][j].get_animals()[A]->get_Alive() == true)			//if current animal is alive
				{
					if(Terrain[i][j].get_animals()[A]->CheckHunger() == true)	//if it is hungry
						Terrain[i][j].get_animals()[A]->Increase_Hunger();		//hungerCount will be increased. If hungry for 10 days: it will die
					else
						Terrain[i][j].get_animals()[A]->Set_Hunger();			//hungerCount is zeroed
				}
				if(Terrain[i][j].get_animals()[A]->get_Alive() == false)		//if it is dead
				{
					Terrain[i][j].get_animals()[A]->get_animalName(name);
					if(Terrain[i][j].get_animals()[A]->get_token() == 'H')		//if it was a herbivore
					{
						n_animals[1]--;											//decreasing total number of herbivores
						if(name == "Deer")
							n_animals[3]--;										//decreasing total number of deers
						else if(name == "Rabbit")
							n_animals[4]--;										//decreasing total number of rabbits
						else if(name == "Groundhog")
							n_animals[5]--;										//decreasing total number of groundhogs
						else if(name == "Salmon")
							n_animals[6]--;										//decreasing total number of salmons
					}
					else														//if it was a carnivore
					{
						n_animals[2]--;											//decreasing total number of carnivores
						if(name == "Fox")
							n_animals[7]--;										//decreasing total number of foxes
						else if(name == "Bear")
							n_animals[8]--;										//decreasing total number of bears
						else if(name == "Wolf")
							n_animals[9]--;										//decreasing total number of wolves
					}
					n_animals[0]--;												//decreasing total number of animals
					Terrain[i][j].EraseAnimals(A);								//deleting dead animal
					A--;														//vector's size got decreased
				}
				A++;															//go to vector's next animal
			}
		}
	}
}

void Ecosystem::AnimalMovement()
{
	char Enviroment;
	bool flag;
	int counter,counterB, place;
	string animal;
	vector <Animal*> Animals;

	for(int i=0; i<terrainSize; i++)								//We are checking the entire Terrain
	{
		for(int j=0; j<terrainSize; j++)
		{
			Animals = Terrain[i][j].get_animals();
			counterB = 0;
			if(Animals.size() > 0)
			{
				for(int A=0; A<Animals.size(); A++)
				{
					if(Animals[A]->get_Alive() == true)
					{
						Animals[A]->get_animalName(animal);
						if(animal=="Deer" || animal=="Wolf" || animal=="Bear" || animal=="Fox")		//They can walk at any place
						{
							flag = false;
							counter = 0;							//The number of our tries
							place = 1 +rand() %4; 					//from 1 up to 4 choiches

							while(flag==false && counter<4)	
							{
								if(place==1 && counter<4)			//up
								{
									counter++;
									if(i > 0 )						//If we are in the top of the terrain,to not overcome him
									{	
										Terrain[i][j].EraseAnimals(A-counterB);		//We kick the animal that it moved
										Terrain[i-1][j].set_animal(Animals[A]);		//We are putting in the new list of animals,the animal that have moved
										flag = true;								//Indeed one animal have moved
										counterB++;
									}
									if(flag == false)
										place++;
								}
								if(place==2 && counter<4)			//down
								{
									counter++;
									if(i < terrainSize-1)			//If we are in the bottom of the terrain
									{
										Terrain[i][j].EraseAnimals(A-counterB);
										Terrain[i+1][j].set_animal(Animals[A]);
										flag = true;
										counterB++;
									}
									if(flag == false)
										place++;
								}
								if(place==3 && counter<4)			//right >
								{
									counter++;
									if(j < terrainSize-1)
									{
										Terrain[i][j].EraseAnimals(A-counterB);
										Terrain[i][j+1].set_animal(Animals[A]);
										flag = true;
										counterB++;
									}
									if(flag == false)
										place++;
								}
								if(place==4 && counter<4)			// < left
								{
									counter++;
									if(j > 0)
									{
										Terrain[i][j].EraseAnimals(A-counterB);
										Terrain[i][j-1].set_animal(Animals[A]);
										flag = true;
										counterB++;
									}
									if(flag == false)
										place=1;
								}
							}
						}
						else if(animal == "Rabbit")
						{
							flag = false;
							counter = 0;							//The number of the tries that we did
							place = 1 +rand() %4;	 				//from 1 up to 4 choiches
							while(flag==false && counter<4)
							{
								if(place==1 && counter<4)			// ^ up
								{
									counter++;
									if(i > 0)						//If we are in the top of the terrain to not overcome him
									{
										Enviroment=Terrain[i-1][j].get_char();
										if(Enviroment != '^')								//If there is hill rabbit cant go there
										{
											Terrain[i][j].EraseAnimals(A-counterB);			//We kick the animal that it moved
											Terrain[i-1][j].set_animal(Animals[A]);			//We are putting in the new list of animals,the animal that have moved
											flag = true;									//Indeed one animal have moved
											counterB++;
										}
									}
									if(flag == false)
										place++;
								}
								if(place==2 && counter<4)			//down
								{
									counter++;
									if(i < terrainSize-1)			//If we are in the bottom of the terrain to not overcome it
									{
										Enviroment=Terrain[i+1][j].get_char();
										if(Enviroment != '^')
										{
											Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i+1][j].set_animal(Animals[A]);
											flag = true;
											counterB++;
										}
									}
									if(flag == false)
										place++;
								}
								if(place==3 && counter<4 )			//right >
								{
									counter++;
									if(j < terrainSize-1)
									{
										Enviroment=Terrain[i][j+1].get_char();
										if(Enviroment != '^')
										{
											Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i][j+1].set_animal(Animals[A]);
											flag = true;
											counterB++;
										}
									}
									if(flag == false)
										place++;
								}
								if(place==4 && counter<4 )			// < left
								{
									counter++;
									if (j > 0 )
									{
										Enviroment=Terrain[i][j-1].get_char();
										if(Enviroment != '^')
										{
											Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i][j-1].set_animal(Animals[A]);
											flag = true;
											counterB++;
										}
									}
									if(flag == false)
										place = 1;
								}
							}
						}
						else if(animal == "Groundhog")
						{
							flag=false;
							counter=0;								//The number of the choiches we have made
							place=1 +rand()%4; 						//from 1 up to 4 choiches
							while(flag==false && counter<4)
							{
								if(place==1 && counter<4)			// ^ up
								{
									counter++;
									if(i > 0)						//If we are in the top of the terrain to not overcome it
									{
										Enviroment=Terrain[i-1][j].get_char();
										if(Enviroment != '#')								//If there is hill groundhog can go there
										{
											Terrain[i][j].EraseAnimals(A-counterB);			//We kick the animal that it moved
											Terrain[i-1][j].set_animal(Animals[A]);			//We are putting in the new list of animals,the animal that have moved
											flag = true;									//Indeed one animal have moved
											counterB++;
										}
									}
									if (flag == false)
										place++;
								}
								if(place==2 && counter<4)			//down
								{
									counter++;
									if(i < terrainSize-1)			//If we are in the bottom of the terrain to not overcome it
									{
										Enviroment=Terrain[i+1][j].get_char();
										if(Enviroment != '#')
										{
										Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i+1][j].set_animal(Animals[A]);
											flag=true;
											counterB++;
										}
									}
									if(flag == false)
										place++;
								}
								if(place==3 && counter<4)			//right >
								{
									counter++;
									if(j < terrainSize-1)
									{
										Enviroment=Terrain[i][j+1].get_char();
										if(Enviroment != '#')
										{
											Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i][j+1].set_animal(Animals[A]);
											flag=true;
											counterB++;
										}
									}
									if(flag == false)
										place++;
								}
								if(place==4 && counter<4)			// < left
								{
									counter++;
									if(j > 0)
									{
										Enviroment=Terrain[i][j-1].get_char();
										if(Enviroment!= '#')
										{
											Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i][j-1].set_animal(Animals[A]);
											flag = true;
											counterB++;
										}
									}
									if(flag == false)
										place=1;
								}
							}
						}
						else if (animal=="Salmon")
						{
							flag=false;
							counter=0;								//The number of the choiches that we made
							place=1 +rand()%4; 						//from 1 up to 4 chochies
							while(flag==false && counter<4)
							{
								if(place==1 && counter<4)			// ^ up
								{
									counter++;
									if(i > 0)						//If we are in the top of the terrain to not overcome it
									{
										Enviroment=Terrain[i-1][j].get_char();
										if(Enviroment!='^' || Enviroment!='"')			//ama exei hill den mporei na paei ekei If there is hill we can't go there
										{
											Terrain[i][j].EraseAnimals(A-counterB);		//We kick the animal that it moved 
											Terrain[i-1][j].set_animal(Animals[A]);		//We are putting in the new list of animals,the animal that have moved
											flag = true;								//Indeed one animal have moved
											counterB++;
										}
									}
									if(flag == false)
										place++;
								}
								if(place==2 && counter<4)			//down, Katw
								{
									counter++;
									if(i < terrainSize-1)			//If we are in the bootom of the map to not overcome it
									{
										Enviroment = Terrain[i+1][j].get_char();
										if(Enviroment!= '^' || Enviroment!='"')
										{
											Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i+1][j].set_animal(Animals[A]);
											flag = true;
											counterB++;
										}
									}
									if(flag == false)
										place++;
								}
								if(place == 3  &&  counter < 4)		//right >
								{
									counter++;
									if(j < terrainSize-1)
									{
										Enviroment = Terrain[i][j+1].get_char();
										if(Enviroment!= '^' || Enviroment!='"')
										{
											Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i][j+1].set_animal(Animals[A]);
											flag = true;
											counterB++;
										}
									}
									if(flag == false)
										place++;
								}
								if(place==4 && counter<4)			// < left
								{
									counter++;
									if(j > 0)
									{
										Enviroment = Terrain[i][j-1].get_char();
										if(Enviroment!= '^' || Enviroment!='"')
										{
											Terrain[i][j].EraseAnimals(A-counterB);
											Terrain[i][j-1].set_animal(Animals[A]);
											flag = true;
											counterB++;
										}
									}
									if(flag == false)
										place=1;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Ecosystem::AnimalEating()
{
	int  	A, HDays;
	bool	Hungry, alive;
	Plant	*plant;
	Animal	*victim;
	string	name, victimName;

	for(int i=0; i<terrainSize; i++)
	{
		for(int j=0; j<terrainSize; j++)
		{
			plant = Terrain[i][j].get_plant();												//get current plant
			if(Terrain[i][j].get_animals().size() > 0)										//if there are animals in vector Tile::animals of current tile
			{
				for(A=0; A<Terrain[i][j].get_animals().size(); A++)							//until all animals of current tile are checked
				{
					if(Terrain[i][j].get_animals()[A]->get_token() == 'H' && plant != NULL  && plant->isDead() == false)	//if current animal is a Herbivore and there is an alive plant on current tile
					{
						if(Terrain[i][j].get_animals()[A]->get_Alive() == true)				//if current animal is alive
						{
							Terrain[i][j].get_animals()[A]->get_animalName(name);
							if(name == "Deer")
							{
								if(plant->get_name() == "Seedless")							//if it is a seedless plant
									Terrain[i][j].get_animals()[A]->Eat(plant);
								else if(plant->get_size() <= (Terrain[i][j].get_animals()[A]->get_size()+4))				//if it is a seeded plant and Deer can eat it
									Terrain[i][j].get_animals()[A]->Eat(plant);
							}
							else if(name == "Rabbit" || name == "Groundhog")
							{
								if(plant->get_token() == 'G')								//if it is Grass (the only seedless plant eaten by Rabbits or Groundhogs)
									Terrain[i][j].get_animals()[A]->Eat(plant);
								else if( (plant->get_name()=="Seeded") && (plant->get_size() <= Terrain[i][j].get_animals()[A]->get_size()) )		//if it is a seeded plant and Rabbit or Groundhog can eat it
									Terrain[i][j].get_animals()[A]->Eat(plant);
							}
						}
					}
					if(Terrain[i][j].get_animals()[A]->get_token() == 'C')					//if current animal is a Carnivore
					{
						Terrain[i][j].get_animals()[A]->get_animalName(name);
						alive = Terrain[i][j].get_animals()[A]->get_Alive();
						if(alive == true  &&  (name == "Fox" || name == "Wolf"))			//if it is alive and is a fox
						{
							for(int v=0; v<Terrain[i][j].get_animals().size(); v++)			//until all animals (possible victims) of current tile's vector are checked
							{
								Hungry = Terrain[i][j].get_animals()[A]->CheckHunger();
								if(Hungry == true)											//if current animal is hungry
								{
									victim = Terrain[i][j].get_animals()[v];				//get possible victim
									victim->get_animalName(victimName);
									if(victim->get_Alive() == true && victim->get_token() == 'H' && victimName != "Salmon")	//if possible victim is alive and is a Herbivore except for Salmon
									{
										if((victim->get_size() <= Terrain[i][j].get_animals()[A]->get_size()) && (victim->get_speed() < Terrain[i][j].get_animals()[A]->get_speed()) )	//if current animal can eat the possible victim
										{
											Terrain[i][j].get_animals()[v]->setDead();						//victim dies
											Terrain[i][j].get_animals()[A]->Eat(victim->get_size());		//current animal eats the victim
										}
									}
									HDays = Terrain[i][j].get_animals()[A]->get_HungerDays();
									if(HDays > 7)											//if current animal has eaten in 7 days or more
									{
										if(v != A && victim->get_Alive() == true && victim->get_token() == 'C' && victimName != "Bear")		//if possible victim is alive and is a Carnivore except for Bear (or itself)
										{
											if((victim->get_size() < Terrain[i][j].get_animals()[A]->get_size()) || (victim->get_size() == Terrain[i][j].get_animals()[A]->get_size() && victim->get_defense() < Terrain[i][j].get_animals()[A]->get_attack()) )	//if current animal can eat the possible victim
											{
												Terrain[i][j].get_animals()[v]->setDead();					//victim dies
												Terrain[i][j].get_animals()[A]->Eat(victim->get_size());	//current animal eats the victim
											}
										}
									}
								}
							}
						}
						else if(alive == true  &&  name == "Bear")							//if current animal is alive and it is a bear
						{
							for(int v=0; v<Terrain[i][j].get_animals().size(); v++)			//until all animals (possible victims) of current tile's vector are checked
							{
								Hungry = Terrain[i][j].get_animals()[A]->CheckHunger();
								if(Hungry == true)											//if current animal is hungry
								{
									victim = Terrain[i][j].get_animals()[v];				//get possible victim

									if((victim->get_Alive() == true) && (victim->get_token() == 'H'))						//if possible victim is alive and it is a Herbivore
									{
										Terrain[i][j].get_animals()[v]->setDead();							//victim dies
										Terrain[i][j].get_animals()[A]->Eat(victim->get_size());			//current animal eats the victim
									}

									HDays = Terrain[i][j].get_animals()[A]->get_HungerDays();
									if(HDays > 7)											//if current animal has not eaten in 7 days or more
									{
										victim->get_animalName(victimName);
										if((victim->get_Alive() == true) && (victim->get_token() == 'C') && (victimName != "Bear"))			//if possible victim is alive and is a Carnivore except for bear
										{
											Terrain[i][j].get_animals()[v]->setDead();						//victim dies
											Terrain[i][j].get_animals()[A]->Eat(victim->get_size());		//current animal eats the victim
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

bool Ecosystem::FindFreeTile(Plant*& plant, Plant*& new_plant, string& place)
{
	int		i, j;
	char	token, ground, proper_ground;

	token = plant->get_token();
	if(token == 'A')									//if it is Algae
		proper_ground = '#';							//lives only in water
	else if(token == 'O')								//if it is an Oak
		proper_ground = '"';							//lives only in meadows
	else												//if it is Grass or Maple or Pine
		proper_ground = '0';							//does not live in water

	plant->get_place(i,j);								//get current plant's coordinates

	if(j > 0)											//if it is not in Terrain's first column
	{
		new_plant = Terrain[i][j-1].get_plant();
		ground = Terrain[i][j-1].get_char();
		if(new_plant == NULL  &&  (proper_ground == ground  ||  (proper_ground=='0' && ground!='#')))			//if the left tile is free and the ground is proper
		{
			place = "left";
			return true;
		}
	}
	if(j < (terrainSize-1))								//if it is not in Terrain's last column
	{
		new_plant = Terrain[i][j+1].get_plant();
		ground = Terrain[i][j+1].get_char();
		if(new_plant == NULL  &&  (proper_ground == ground  ||  (proper_ground=='0' && ground!='#')))			//if the right tile is free and the ground is proper
		{
			place = "right";
			return true;
		}
	}
	if(i > 0)											//if it is not in Terrain's first row
	{
		new_plant = Terrain[i-1][j].get_plant();
		ground = Terrain[i-1][j].get_char();
		if(new_plant == NULL  &&  (proper_ground == ground  ||  (proper_ground=='0' && ground!='#')))			//if the upper tile is free and the ground is proper
		{
			place = "up";
			return true;
		}
	}
	if(i < (terrainSize-1))								//if it is not in Terrain's last row
	{
		new_plant = Terrain[i+1][j].get_plant();
		ground = Terrain[i+1][j].get_char();
		if(new_plant == NULL  &&  (proper_ground == ground  ||  (proper_ground=='0' && ground!='#')))			//if the down tile is free and the ground is proper
		{
			place = "down";
			return true;
		}
	}
	//if(new_plant != NULL)								//if the surrounding tiles are not free or the ground is not proper
	return false;
}

void Ecosystem::PlantBreeding(int season)
{
	Plant	*plant, *new_plant;
	int		BreedingRepPeriod, breeding;
	string	place;
	char	token;

	for(int i=0; i<terrainSize; i++)
		for(int j=0; j<terrainSize; j++)
		{
			plant = Terrain[i][j].get_plant();						//get current plant
			if((plant != NULL) && (plant->isDead() == false))		//if there is an alive plant
			{
				plant->get_breedingRepPeriod(BreedingRepPeriod);
				if((BreedingRepPeriod != 0) && (dayOfYear%BreedingRepPeriod == 0))		//if it is plant's breeding period
				{
					breeding = rand() %100 + 1;						//from 1 up to 100
					if(breeding <= plant->get_breedingProb())		//if it can breed
					{
						token = plant->get_token();
						if(FindFreeTile(plant, new_plant, place) == true)				//if one of the surrounding tiles is free
						{
							if(place == "left")						//if the left tile is free
							{
								plant->Breeding(token,i,j-1,new_plant,season);
								Terrain[i][j-1].get_plant() = new_plant;
							}
							else if(place == "right")				//if the right tile is free
							{
								plant->Breeding(token,i,j+1,new_plant,season);
								Terrain[i][j+1].get_plant() = new_plant;
							}
							else if(place == "up")					//if the upper tile is free
							{
								plant->Breeding(token,i-1,j,new_plant,season);
								Terrain[i-1][j].get_plant() = new_plant;
							}
							else //if(place == "down")				//if the down tile is free
							{
								plant->Breeding(token,i+1,j,new_plant,season);
								Terrain[i+1][j].get_plant() = new_plant;
							}
							n_plants[0]++;							//increasing total number of plants
							if(token == 'A')						//if it is Algae
								n_plants[1]++;						//increasing total number of Algae
							else if(token == 'M')					//if it is a Maple
								n_plants[2]++;						//increasing total number of Maples
							else if(token == 'P')					//if it is a Pine
								n_plants[3]++;						//increasing total number of Pines
							else if(token == 'G')					//if it is Grass
								n_plants[4]++;						//increasing total number of Grass
							else if(token == 'O')					//if it is an Oak
								n_plants[5]++;						//increasing total number of Oaks
						}
					}
				}
			}
		}
}

void Ecosystem::AnimalBreeding(int season)
{
	bool	InHibernation;
	int		Breeding, Max, growth, breedingC, breedingH, size;
	string	animal;

	if(season == 1)					//Spring
	{
		growth = 20;
		breedingC = 11;
		breedingH = 12;
		InHibernation = false;		//only for Bear and Groundhog
	}
	else if(season == 2)			//Summer
	{
		growth = 30;
		breedingC = 9;
		breedingH = 8;
		InHibernation = false;		//only for Bear and Groundhog
	}
	else if(season == 3)			//Autumn
	{
		growth = 15;
		breedingC = 9;
		breedingH = 5;
		InHibernation = false;		//only for Bear and Groundhog
	}
	else if(season == 4)			//Winter
	{
		growth = 30;
		breedingC = 10;
		breedingH = 18;
		InHibernation = true;		//only for Bear and Groundhog, all animals excep Bears and Groundhogs have: Animal::hibernates = false
	}

	for (int i=0; i<terrainSize; i++)
	{
		for (int j=0; j<terrainSize; j++)
		{
			if(Terrain[i][j].get_animals().size() > 0)								//if there are animals in vector Tile::animals of current tile
			{
				size = Terrain[i][j].get_animals().size();
				for(int A=0; A<size; A++)											//only the already existing (adult) animals will breed (and not the newly created Salmons)
				{
					if(Terrain[i][j].get_animals()[A]->get_Alive() == true)			//if current animal is alive
					{
						Terrain[i][j].get_animals()[A]->get_Breeding(Breeding);
						if((dayOfYear%Breeding) == 0)								//if it is a breeding period
						{
							Terrain[i][j].get_animals()[A]->get_animalName(animal);
							if(animal == "Fox")
							{
								Max = Terrain[i][j].get_animals()[A]->get_speed();
								if(Max == 6)										//if current animal is adult
								{
									Terrain[i][j].set_animal(new Carnivores("Fox",2,1,'C',0,1,i,j,true,true,0,0,false,false,false,1,1));
									Terrain[i][j].get_animals()[Terrain[i][j].get_animals().size()-1]->Set_Period(growth,breedingC,false);
									n_animals[0]++;									//increasing total number of animals
									n_animals[2]++;									//increasing total number of carnivores
									n_animals[7]++;									//increasing total number of foxes
								}
							}
							else if(animal == "Wolf")
							{
								Max = Terrain[i][j].get_animals()[A]->get_size();
								if(Max == 7)										//if current animal is adult
								{
									Terrain[i][j].set_animal(new Carnivores("Wolf",2,1,'C',0,2,i,j,true,true,0,0,false,false,false,8,6));
									Terrain[i][j].get_animals()[Terrain[i][j].get_animals().size()-1]->Set_Period(growth,breedingC,false);
									n_animals[0]++;									//increasing total number of animals
									n_animals[2]++;									//increasing total number of carnivores
									n_animals[9]++;									//increasing total number of wolves
								}
							}
							else if(animal == "Bear")
							{
								Max = Terrain[i][j].get_animals()[A]->get_size();
								if(Max == 10)										//if current animal is adult
								{
									Terrain[i][j].set_animal(new Carnivores("Bear",5,3,'C',0,4,i,j,true,true,0,0,true,true,false,10,10));
									Terrain[i][j].get_animals()[Terrain[i][j].get_animals().size()-1]->Set_Period(growth,breedingC,InHibernation);
									n_animals[0]++;									//increasing total number of animals
									n_animals[2]++;									//increasing total number of carnivores
									n_animals[8]++;									//increasing total number of bears
								}
							}
							else if(animal == "Deer")
							{
								Max = Terrain[i][j].get_animals()[A]->get_size();
								if(Max == 5)										//if current animal is adult
								{
									Terrain[i][j].set_animal(new Herbivores("Deer",'H',2,4,4,i,j,true,true,0,0,0,false,false,false,false));
									Terrain[i][j].get_animals()[Terrain[i][j].get_animals().size()-1]->Set_Period(growth,breedingH,false);
									n_animals[0]++;									//increasing total number of animals
									n_animals[1]++;									//increasing total number of herbivores
									n_animals[3]++;									//increasing total number of deers
								}
							}
							else if(animal == "Rabbit")
							{
								Max = Terrain[i][j].get_animals()[A]->get_speed();
								if(Max == 6)										//if current animal is adult
								{
									Terrain[i][j].set_animal(new Herbivores("Rabbit",'H',1,2,2,i,j,true,true,0,0,0,false,false,false,false));
									Terrain[i][j].get_animals()[Terrain[i][j].get_animals().size()-1]->Set_Period(growth,breedingH,false);
									n_animals[0]++;									//increasing total number of animals
									n_animals[1]++;									//increasing total number of herbivores
									n_animals[4]++;									//increasing total number of rabbits
								}
							}
							else if(animal == "Groundhog")
							{
								Max = Terrain[i][j].get_animals()[A]->get_speed();
								if(Max == 5)										//if current animal is adult
								{
									Terrain[i][j].set_animal(new Herbivores("Groundhog",'H',2,3,3,i,j,true,true,0,0,0,true,true,true,false));
									Terrain[i][j].get_animals()[Terrain[i][j].get_animals().size()-1]->Set_Period(growth,breedingH,InHibernation);
									n_animals[0]++;									//increasing total number of animals
									n_animals[1]++;									//increasing total number of herbivores
									n_animals[5]++;									//increasing total number of groundhogs
								}
							}
							else if(animal == "Salmon")								//Salmon is born adult
							{
								Terrain[i][j].set_animal(new Herbivores("Salmon",'H',1,5,1,i,j,true,true,0,0,0,false,false,false,false));
								Terrain[i][j].get_animals()[Terrain[i][j].get_animals().size()-1]->Set_Period(growth,breedingH,false);
								n_animals[0]++;										//increasing total number of animals
								n_animals[1]++;										//increasing total number of herbivores
								n_animals[6]++;										//increasing total number of salmons
							}
						}
					}
				}
			}
		}
	}
}

void Ecosystem::PrintSystem()
{
	Plant	*plant;

	cout << "\nCurrent Day: " << dayOfYear << endl;
	for(int i=0; i<terrainSize; i++)
	{
		for(int j=0; j<terrainSize; j++)
		{
			plant = Terrain[i][j].get_plant();
			if((plant != NULL) && (plant->isDead() == false))			//if there is an alive plant
				cout /*<< "Plant: "*/ << plant->get_token() << ' ';
			else
				cout /*<< "Tile: "*/ << Terrain[i][j].get_char() << ' ';
		}
		cout << endl;
	}
	cout << endl;
	cout << "Total number of plants: " << n_plants[0] << endl;
	cout << "Total number of animals: " << n_animals[0] << endl;
	cout << "Total number of herbivores: " << n_animals[1] << endl;
	cout << "Total number of carnivores: " << n_animals[2] << endl;
}

void Ecosystem::PrintPlantStatistics()
{
	cout << "\nTotal number of Algae: " << n_plants[1] << endl;
	cout << "Total number of Maples: " << n_plants[2] << endl;
	cout << "Total number of Pines: " << n_plants[3] << endl;
	cout << "Total number of Grass: " << n_plants[4] << endl;
	cout << "Total number of Oak: " << n_plants[5] << endl;
}

void Ecosystem::PrintAnimalStatistics()
{
	cout << "\nTotal number of Deers: " << n_animals[3] << endl;
	cout << "Total number of Rabbits: " << n_animals[4] << endl;
	cout << "Total number of Groundhogs: " << n_animals[5] << endl;
	cout << "Total number of Salmon: " << n_animals[6] << endl;
	cout << "Total number of Foxes: " << n_animals[7] << endl;
	cout << "Total number of Bears: " << n_animals[8] << endl;
	cout << "Total number of Wolves: " << n_animals[9] << endl;
}

void Ecosystem::RunEcosystem(int days)
{
	enum Seasons{Spring=1, Summer, Autumn, Winter};		//enum from 1 up to 4
	int season = rand() %4 + 1;							//from 1 up to 4
	int d, hours;

	ApplySeason(season);								//start simulation on a randomly specified season

	for(d=1; d<=days; d++)								//one day/simulation cycle
	{
		DailyReset();									//start a new day

		if(d == 1)										//if it is simulation's first day
		{
			PrintSystem();
			PrintPlantStatistics();
			PrintAnimalStatistics();
		}

		if(dayOfYear%90 == 1 && dayOfYear != 1)			//if it is the start of a new seeason
		{
			if(season == Winter)
				season = Spring;
			else
				season++;

			ApplySeason(season);						//go to the next season

			PrintSystem();
			PrintPlantStatistics();
			PrintAnimalStatistics();
		}

		for(hours=1; hours<=24; hours++)				//animals move and eat every hour
		{
			AnimalMovement();
			AnimalEating();
		}

		CheckDeadEntities();
		PlantBreeding(season);
		AnimalBreeding(season);
	}

	if(days%90 != 1)									//if it is simulation's last day and not the start of a new season (already printed)
	{
		PrintSystem();
		PrintPlantStatistics();
		PrintAnimalStatistics();
	}
}
