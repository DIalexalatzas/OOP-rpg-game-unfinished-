#include<iostream>
#include<cstring>
#include<cstdlib>
#include<random>
#include<time.h>

using namespace std;
//Notes: with the exception of some destructors, every class and subclass in this program has both
//its constructor and its basic 3 functions (copy constructor, destructor, asignment). This was done for 2 reasons:
//1. I dont trust DevC++ to compile and, most importanly, to run my program like a linux environment would.
//2. I wanted to practice certain coding techniques. This led to some bugs( noteably one regarding assignment ).

//Moreover, the implementation of the print functions every base class(Item, Spell, Living) has been left to the
//subclasses in order to achieve a more natural flow of information(for example, it would be unintuitive for a player
//to see the price of a weapon before its attack, or the duration of a spells effect before said duration. Since
//items that dont belong to any subclass don't have a relevance in the game, the print functions in the base classes
//remain purely virtual. They are still declared and implemented, however, for the inventory functions.

//

//Current To Do List:
//Create Copy Constructor and Assignment Function for classes with strings ASAP
//Check the Inventory related functions for errors
//Create "Empty Bottle" function for further work on the project
//Make Use functions for Spells void

//Log
//1/10/2021 (04:00): Implementation of Item Class and Subclasses completed. Bug Testing reserved for later date.
//1/11/2021 (01:44): Implementation of Spell Class and Subclasses completed. Bug testing reseerved for later date.  
//1/12/2021 (01:41): Implementation of Hero Class and Subclasses complete. Implementation of Living Class Complete. Bug testing reserved for later date. Optimization of print functions.
//1/12/2021 (23:06): Implementation of Monster Class and subclasses complete. Bug Testing reserved for later date.
//1/14/2021 (00.47): Implementation of Grid class completed. Bug testing reserved for later date. Shop Items created.

//just regular maximum and minimum function templates

template <class T>
T get_max( T a , T b ){
	
	return ( a > b ? a : b ) ;
	
}

template <class T>
T get_min( T a , T b ){
	
	return ( a < b ? a : b ) ;
	
}

//2 useful structs which will be used later, specifically for the Spell and Grid Classes. Not made with a template in order to make the
//code less confusing.

struct range{
	
	double min ;
	double max ;
	
};

struct coordinates{
	
	int x ;
	int y ;
	
};

const range blankrange = { 0 , 0 } ;
const coordinates O = { 0 , 0 } ;
//declarations

 
class Hero ;
class Item ;
class Living ;
class Monster ;






//Item class and subclasses

class Item{
	
	public:
		
//constructors/destructor
		
		Item( const char* , const double , const int , const int ) ;
		Item( const Item& ) ;
		~Item() ;
		
//assignment 

		Item& operator=( const Item& ) ;
		
// get functions		

		const char* get_name()const{ return name ; }
		double get_price()const{ return price ; }
		int get_minlvl()const{ return minlvl ; }
		int get_type()const{ return type ;}		
//set functions
		
		void set_name( const char* ) ;
		void set_price( const double ) ;
		void set_minlvl( const int ) ;
		
		
//gameplay implementation
			
		virtual void equip( Hero& ){ return ;}
		virtual void unequip( Hero& ){ return ;}
		virtual void use( Hero& ){ return ;} 

//print functions
	
		virtual void print_all()const{ return ;}	
		
	protected:
		
//another assignment procedure I used to work around a very annoying bug. Only used by subclasses.
		void equals( const Item& ) ;
	
	protected:
		
		bool isUsed ;
		
	private:
		
		char* name ;
		double price ;
		int minlvl ;
		int type ; // can be 1 for Weapon, 2 for Armor or 3 for potion
		
		
};





class Weapon : public Item{
	
	public:

//constructors/destructor
		
		Weapon( const char* , const double , const int , const int , const double , const int ) ;
		Weapon( const Weapon& ) ;
//		~Weapon() ; uneeded. Default destructor works fine for this subclass.
		
//assigment functions
	
		Weapon& operator=( const Weapon& ) ;		
		
		
//get functions(Set functions unneeded)
		
		double get_dmg()const{ return dmg ; }
		
//gameplay implementation
		
		void equip( Hero& ) ;
		void unequip( Hero& ) ;
//		void use( Hero& ){ return ; } ;
		
// print functions		
		
		void print_all()const ;
			
	private:
		
		double dmg ;
		int hands ; //can be 0 , 1 , 2
	
};

class Armor : public Item{
	
	public:
		
//constructors/destructor		
		
		Armor( const char* , const double , const int , const int , const double ) ;
		Armor( const Armor& ) ;
//		~Armor() ; Uneeded. Default destructor works fine for this subclass.

//assignment functions

		Armor& operator=( const Armor& ) ;
		
//get functions(set functions unneeded)		
		
		double get_def()const{ return def ;}
		bool get_isWorn()const{ return def ;}
		
//gameplay implementation	
		
		void equip( Hero& ) ; 
		void unequip( Hero& ) ;
//		void use( Hero& ) = 0 ;
		
//print functions		
		
		void print_all()const ;
		
	private:
		
		double def ;

};

class Potion : public Item{
	
	public:
		
//constructors/destructor		
		
		Potion( const char* , const double , const int , const int , const int , const double ) ;
		Potion( const Potion& ) ;
//		~Potion() ;
		
//assignment functions		

		Potion& operator=( const Potion& ) ;
		
//gameplay implementation(Unique one-time use nature of potions requires unique function. )
		
		void use( Hero& ) ;
		
//		void equip( Hero& ) = 0 ;
//		void unequip( Hero& ) { return ; }
		
//print functions		
		
		void print_all()const ;
		
	private:
		
		int stat ; //can be 1 for ATK, 2 for SOR, 3 for AGL, 4 for HP or 5 for MP
		double up ;
		
};



//Item constructors, destructors

Item::Item( const char* n = "NONE" , const double p = 0 , const int l = 0 , const int t = 0 ) : price(p) , minlvl(l), type(t) , isUsed(0){ //Items with type 0 will be considered non existent
	
	name = new char[ strlen( n ) + 1 ];
    strcpy( name , n ) ;
	
}

Item::Item( const Item& I ) : price(I.price) , minlvl(I.minlvl) , type(I.type) , isUsed(0){
	
	name = new char[ strlen( I.name ) + 1 ];
    strcpy( name , I.name ) ;
	
}


Item::~Item(){
	
	delete[] name ;
	
}

Weapon::Weapon( const char* n = "NONE" , const double p = -1 , const int l = 0 , const int t = 1 , const double d = 0 , const int h = 0 ): 
dmg(d)  , Item( n , p , l , t ) {
	
	hands = get_min( 2 , get_max( 0 , h ))	;
	
}

Weapon::Weapon( const Weapon& A ): 
dmg( A.dmg )  , Item( A ) {
	
	if ( A.hands > 2){
		
		hands = 2 ;
		
	}else if ( A.hands < 0 ){
		
		hands = 0 ;
		
	}else{
		
		hands = A.hands ;
		
	}
	
	
}


Armor::Armor( const char* n = "NONE" , const double p = -1 , const int l = 0 , const int t = 2 , const double d = 0 ) : 
def(d) , Item( n , p , l , t ){}

Armor::Armor( const Armor& A ) : def( A.def ) ,  Item(A){}

Potion::Potion( const char* n = "NONE" , const double p = -1 , const int l = 0 , const int t = 3 , const int s = 1 , const double u = 0  ) :
stat(s) , up(u) , Item( n , p , l , t ){}

Potion::Potion( const Potion& A ) : stat( A.stat ) , up( A.up ) , Item( A ){}









//Spell class and subclasses

class Spell{
	
	public:
		
//constructors/destructors 		

		Spell( const char* , const double , const int , const double , const double , const double , const int , const int ) ;
		Spell( const char* , const double , const int , const range , const double , const int ) ;
		Spell( const Spell& ) ;
		~Spell() ;
		
//assingment functions

		Spell& operator=( const Spell& ) ;

//get functions
	
		char* get_name()const{ return name ; }
		double get_price()const{ return price ; }
		int get_minlvl()const{ return minlvl ; }
		range get_dmg()const{ return dmg ; }
		double get_magic()const{ return magic ; }	
		int get_dur()const{ return dur ; }	
		int get_type()const{ return type ;}
		
//set functions

		void set_name( const char* ) ;
		void set_price( const double ) ;
		void set_minlvl( const int ) ;
		void set_dmg( const range ) ;
		void set_magic( const double ) ;
		void set_dur( const int ) ;
//gameplay implementation

		virtual int use( Hero& , Monster&, double& ){ return dur ; } //returns number of turns debuff lasts and monster's defense.
		virtual int use( Hero& , Monster&, range& ){ return dur ; }
		
//print functions		
		
		virtual void print_all()const{ return ; }
		
	protected:
		
//same as before
	
		void equals( const Spell& ) ;	
			
	private:
	
		char* name ;
		double price ;
		int minlvl ;
		range dmg ;
		double magic ;
		int dur ;
		int type ;
		
};

class IceSpell : public Spell{
	
	public:

//constructors/destructor
		
		IceSpell( const char* , const double , const int , const double , const double , const double , const int , const double ) ;
		IceSpell(  const char* , const double , const int , const range , const double , const int , const double ) ;
		IceSpell( const IceSpell& ) ;
//		~IceSpell() ;
		
//assignment functions

		IceSpell& operator=( const IceSpell& ) ;
		
//get functions
		
		double get_AtkRedu()const{ return AtkRedu ; }		

//set functions

		void set_AtkRedu()const ;
	
//gameplay implementation

		int use( Hero& , Monster& , range& ) ;
		
//print functions

		void print_all()const ;	
	
	private:
		
		double AtkRedu ; //between 0 and 100
		
};

class FireSpell : public Spell{
	
	public:
	
//constructors/destructor		
		
		FireSpell( const char* , const double , const int , const double , const double , const double , const int , const double ) ;
		FireSpell(  const char* , const double , const int , const range , const double , const int , const double ) ;
		FireSpell( const FireSpell& ) ;
//		~FireSpell() ;

//assignment functions

		FireSpell& operator=( const FireSpell& ) ;
		
//get functions
		
		double get_DefRedu()const{ return DefRedu ; }		

//set functions

		void set_DefRedu()const ;
		
//gameplay implementation

		int use( Hero& , Monster& , double& ) ;
		
//print functions

		void print_all()const ;	
		
	private:
		
		double DefRedu ;//between 0 and 100
	
};

class LightningSpell : public Spell{
	
	public:
		
//constructors/destructor		
		
		LightningSpell( const char* , const double , const int , const double , const double , const double , const int , const double ) ;
		LightningSpell(  const char* , const double , const int , const range , const double , const int , const double ) ;
		LightningSpell( const LightningSpell& ) ;
//		~LightningSpell() ;

//assignment functions

		LightningSpell& operator=( const LightningSpell& ) ;
		
//get functions
		
		double get_EvRedu()const{ return EvRedu ; }		

//set functions

		void set_EvRedu()const ;
	
	
//gameplay implementation

		int use( Hero& , Monster& , double& ) ;
		
//print functions

		void print_all()const ;	
	
	private:
		
		double EvRedu ; //between 0 and 100
	
};


//Spell constructors/destructor

Spell::Spell( const char* n = "NONE" , const double p = 0 , const int l = 0 , const double max = 0 , const double min = 0 , const double m = 0, const int i = 0 ,const int t = 0 ) :
minlvl( l ) , price( p ) , magic( m ) , dur( i ) , type(t){
	
	name = new char[ strlen(n) + 1 ] ;
	strcpy( name , n ) ;
	dmg.max = max ;
	dmg.min = min ;
	
}


Spell::Spell( const Spell& A ) :
minlvl( A.minlvl ) , price( A.price ) , magic( A.magic ) , dur( A.dur ) , type(A.type){
	
	name = new char[ strlen(A.name) + 1 ] ;
	strcpy( name , A.name ) ;
	dmg.max = A.dmg.max ;
	dmg.min = A.dmg.min ;
	
}

Spell::~Spell(){
	
	delete[] name ;
	
}

//IceSpell constructors

IceSpell::IceSpell( const char* n = "NONE" , const double p = 0 , const int l = 0 , const double max = 0 , const double min = 0 , const double m = 0 , const int i = 0 , const double r = 0 ) :
AtkRedu(r) , Spell( n , p , l , max , min , m , i , 1 ){}

IceSpell::IceSpell( const IceSpell& A ) : AtkRedu( A.AtkRedu ) , Spell( A ){} 

//FireSpell constructors

FireSpell::FireSpell( const char* n = "NONE" , const double p = 0 , const int l = 0 , const double max = 0 , const double min = 0 , const double m = 0 , const int i = 0 , const double r = 0 ) :
DefRedu(r) , Spell( n , p , l , max , min , m , 2 ){}

FireSpell::FireSpell( const FireSpell& A ) : DefRedu( A.DefRedu ) , Spell( A ){} 

//Lightning constructors

LightningSpell::LightningSpell( const char* n = "NONE" , const double p = 0 , const int l = 0 , const double max = 0 , const double min = 0 , const double m = 0 , const int i = 0 , const double r = 0 ) :
EvRedu(r) , Spell( n , p , l , max , min , m , 3 ){}

LightningSpell::LightningSpell( const LightningSpell& A ) : EvRedu( A.EvRedu ) , Spell( A ){} 















//Living class

class Living{
	
	public:
		
//constructors/destructor		
		
		Living(  const char* , const double , const int ) ;
		Living( const Living&  ) ;
		~Living() ;
	
//assignment function

		virtual Living& operator=( const Living& ) ;	
		
//get functions		
		
		double get_hp()const{ return hp ; }
		char* get_name()const{ return name ; }
		int get_lvl()const{ return lvl ; }
	
//set functions	
	
		void set_hp( const double ) ;
		void set_name( const char* ) ;
		void set_lvl( const int ) ;

//gameplay implementation
		
		void check_hp()const ;
		void restore_hp(){ hp = get_min( max_hp , 0.1 * max_hp + hp ) ; }
		
//print functions

		virtual void print_all()const = 0 ;
	
	protected:
		
		double max_hp ;
		
	private:
		
		char* name ;
		double hp ;
		int lvl ;
		
};


//Hero class and subclasses

class Hero : public Living{
	
	friend class Item ;
	friend class armor ;
	
	public:

//constructors/destructor
		
		Hero( const char* , const double , const double , const double ) ;
		Hero( const Hero& ) ;
		~Hero();

//Assignment
		
		Hero& operator=( const Hero& ) ;
		
//get functions
		
		double get_money()const{ return money ;}
		double get_str()const{ return str ; }
		double get_mp()const{ return mp ; }
		double get_dex()const{ return dex ; }
		double get_agl()const{ return agl ; }
		int get_hands()const{ return hands ; }
		int get_amr()const{ return amr ; }
		Item get_Inv( int i )const{ return *Inventory[i] ;}
		Spell get_Tome( int i )const{ return *Tome[i] ; }
//		bool get_wearsArmor()const{ return wearsArmor ; } unneeded
//		double get_exp()const{ return exp ; }

//set functions
		
		void set_money( const double ) ;
		void set_str( const double ) ;
		void set_mp( const double ) ;
		void set_dex( const double ) ;
		void set_agl( const double ) ;
		void set_hands( const int ) ;
		void set_amr( const double ) ; 
//		void set_wearsArmor( const bool ) ; unneeded, function for wearing implemented in Armor function
//		void set_exp( const double ) ;

//gameplay implementation
		
		void addInv( Item& ) ;
		void removeInv( const int ) ;
		void addTome( Spell& ) ;
		void removeTome( const int ) ;
		virtual void reward( const double ) ;
		void attack( Monster& ) ;
		void buyIt( Item& ) ;
		void sellIt( const int ) ;
		void buySp( Spell& ) ;
		void sellSp( const int ) ;
		void restore_mp(){ mp = get_min( max_mp , mp + 0.1 * max_mp ) ;  }
		void punish(){ money = money/2.0 ; Check_hp() ; }
		void unequip_all() ;
		void Equip_Use( const int ) ;
		void Use_Spell( const int , Monster& , range& Prev ) ;
		void Use_Spell( const int , Monster& , double& Prev ) ;
		void Check_hp() ;
		
//print functions
		
		virtual void print_all()const ;	
		void print_inv()const ;
		void print_tome()const ;	
	
	protected:
	
		double exp ;  //between 0 and 100	
		double max_mp ;
		double money ;
		
	private:
		
		double mp ;
		double str ;
		double dex ;  //between 0 and 100
		double agl ;  //between 0 and 100
		int hands ;
		double amr ;
		
		Item *Inventory[10] ; //might make it static later
		Spell *Tome[3] ;
		
};

class Warrior : public Hero{ //high str and agl
	
	public:
	
//constructors/destructor
		
		Warrior( const char* ) ;
		Warrior(const Warrior& ) ;
//		~Warrior() ;

//gameplay implementation
		
		void reward( const double ) ;

//print functions
		
		void print_all()const ;
			
};

class Sorcerer : public Hero{ //high dex and agl
	
	public:
		
//constructors/destructor		
		
		Sorcerer( const char* ) ;
		Sorcerer( const Sorcerer& ) ;
//		~Sorcerer()
		
//gameplay implementation		
		
		void reward( const double ) ;
		
//print functions

		void print_all()const ;		
		
};

class Paladin : public Hero{ //high str and dex
	
	public:
	
//constructors/destructor
		
		Paladin( const char* ) ;
		Paladin( const Paladin& ) ;
//		~Paladin()

//gameplay implementation

		void reward( const double ) ;

//print functions

		void print_all()const ;		
		
};




















//Living constructors and destructor


Living::Living( const char* n = "NPC" , const double h = 10 , const int l = 1 ) : hp(h) , max_hp(h) , lvl(l) {	

	name = new char[ strlen( n ) + 1 ] ;
	strcpy( name , n ) ;
	
}


Living::Living( const Living& A) : hp(A.hp) , lvl(A.lvl) {
	
	name = new char[ strlen( A.name ) + 1 ] ;
	strcpy( name , A.name ) ;
	
}

Living::~Living(){
	
//	cout << "Deleting Living..." << endl ;
	delete[] name ;
	
}

//Hero constructors and destructor

Hero::Hero( const char* n = "NPC" , const double s = 5 , const double d = 1 , const double a = 0.5 ) : 
mp(10) , max_mp(10) , str(s) , dex(d) , agl(a) , money(0) , exp(0) , hands(2) , amr(0) , Living( n , 40 , 1 ){
	
	int i = 0 ;
	
	for ( i = 0 ; i < 10 ; i++ ){
		
		Inventory[i] = new Item ;
		
	}
	
	for ( i = 0 ; i < 3 ; i++){
		
		Tome[i] = new Spell ;
		
	}
			

}

Hero::Hero( const Hero& A ):
mp(10) , str(A.str) , dex(A.dex) , agl(A.agl) , money(0) , exp(0) , hands(2) , amr(0) , Living( A ){
	
	int i = 0 ;
	
	for ( i = 0 ; i < 10 ; i++ ){
		
		if( A.get_Inv(i).get_type() == 1 ){
			
			Inventory[i] = new Weapon ;
			*Inventory[i] = A.get_Inv(i) ;
			
		}else if( A.get_Inv(i).get_type() == 2 ){
			
			Inventory[i] = new Armor ;
			*Inventory[i] = A.get_Inv(i) ;
			
		}else if( A.get_Inv(i).get_type() == 3 ){
			
			Inventory[i] = new Potion ;
			*Inventory[i]=A.get_Inv(i) ;
			
		}else{
			
			Inventory[i] = new Item ;
			
		}
		
	}
	
	for ( i = 0 ; i < 3 ; i++){
		
		
		if( A.get_Tome(i).get_type() == 1 ){
			
			Tome[i] = new IceSpell ;
			*Tome[i] = A.get_Tome(i) ;
			
		}else if( A.get_Tome(i).get_type() == 2 ){
			
			Tome[i] = new FireSpell ;
			*Tome[i] = A.get_Tome(i) ;
			
		}else if( A.get_Inv(i).get_type() == 3 ){
			
			Tome[i] = new LightningSpell ;
			*Tome[i] = A.get_Tome(i) ;
			
		}else{
			
			Tome[i] = new Spell ;
			
		}
		
	}
	
}

Hero::~Hero(){
	
	int i = 0 ;
	
	for ( i = 0 ; i < 10 ; i++ ){
		
		delete Inventory[i] ;
		
	}
	
	for ( i = 0 ; i < 3 ; i++){
	
		delete Tome[i] ;
	 	
	}
	
}

Warrior::Warrior( const char* n = "NPC" ) : Hero( n , 15 , 1 , 1){}

Sorcerer::Sorcerer( const char* n = "NPC" ) : Hero( n , 10 , 2 , 1){}	

Paladin::Paladin( const char* n = "NPC" ) : Hero( n , 15 , 2 , 0.5 ){}



//monster and subclasses

class Monster : public Living{
 	
	public:
		
//Constructors/destructor		
		
		Monster( const char* , const double , const int , const double , const double , const double , const double ) ;
		Monster( const Monster& ) ;
//		~Monster() ;

//assignment

		Monster& operator=( const Monster& ) ;

//get functions
		
		range get_dmg()const{ return dmg ; }
		double get_def()const{ return def ; }
		double get_agl()const{ return agl ; }

//set functions
		
		void set_dmg( const range ) ;
		void set_def( const double ) ;
		void set_agl( const double ) ;
//		void set_lvl( const int ) ; unneeded

//gameplay implementation
		
		void attack( Hero& ) ;
 		
//print functions

		virtual void print_all()const ;	
 		
	protected:
	
		range dmg ;
		double def ;	
		double agl ; //between 0 and 100
 		
};

class Dragon : public Monster{
	
	public:
		
		Dragon( const char* , const int ) ;
		Dragon( const Dragon& ) ;
//		~Dragon() ;

		void print_all()const ;
		
};

class Exoskeleton : public Monster{
	
	public:
		
		Exoskeleton( const char* , const int ) ;
		Exoskeleton( const Exoskeleton& ) ;
//		~Exoskeleton() ;
		
		void print_all()const ;
	
};

class Spirit : public Monster{
	
	public:
		
		Spirit( const char* , const int ) ;
		Spirit( const Spirit& ) ;
//		~Spirit() ;
		
		void print_all()const ;
		
};

//Monster constructors and destructor


Monster::Monster( const char* n = "NPC" , const double h = 10 , const int l = 1 , const double t = 0 , const double b = 0 , const double d = 0 , const double a = 0 ):
def(d + l*0.2) , agl(a/(51 - 0.5*l)) , Living( n , l + h , l ){

	dmg.max = get_max( t + 0.7*l , b + 0.7*l ) ;
	dmg.min = get_min( t + 0.7*l , b + 0.7*l );

}

Monster::Monster( const Monster& A ):
def( A.def ) , 	agl( A.agl ) , Living( A ){

	dmg.max = A.dmg.max ;
	dmg.min = A.dmg.min ;

}

Dragon::Dragon( const char* n , const int l ):
Monster( n , 5 , l , 5 , 2 , 3 , 1 ){}

Dragon::Dragon( const Dragon& A ):
Monster( A ){}

Exoskeleton::Exoskeleton( const char* n , const int l ) :
Monster( n , 5 , l , 3 , 1 , 3 + 0.1*l , 1 ){}

Exoskeleton::Exoskeleton( const Exoskeleton& A ):
Monster( A ){}

Spirit::Spirit( const char* n , const int l ):
Monster( n , 5 , l , 3 , 1 , 3 , 1 + 0.05*l ){}

Spirit::Spirit( const Spirit& A ):
Monster( A ){}







class Grid{  //5x5 grid
	
	public:
	
//constructors/destructor

		Grid( const coordinates , const coordinates, const coordinates, const coordinates, const coordinates ) ;
		//~Grid()		
	
//gameplay implementation	
		
		void reset(); 
		int move( const char ) ;
		void open_market() ;
		
//print functions		
		
		void print_Map()const ;
		
	private:
		
		coordinates curcord , market ;
		coordinates nonacc[4];
		 
};


Grid::Grid( const coordinates C1 , const coordinates C2 , const coordinates C3 , const coordinates C4 ,  const coordinates m ){
	
	int i = 0 ;
	
	curcord.x = 2 ;
	curcord.y = 2 ;
	
	market = m ;
	
	nonacc[0] = C1 ;
	nonacc[1] = C2 ;
	nonacc[2] = C3 ;
	nonacc[3] = C4 ;
	
}

































//Item functions

void Item::set_name( const char* n ){
	
	delete[] name ;
	name = new char[ strlen( n ) + 1 ];
    strcpy( name , n ) ;
	
}

void Item::set_price(const double p ){
	
	price = p ;
	
}

void Item::set_minlvl(const int l ){
	
	minlvl = l ;
	
}

//currently unneeded
//void Item::print_name()const{
//
//	cout << "Name: " << name << endl ;
//
//}

Item& Item::operator=( const Item& A ){
	
	delete[] name ;
	name = new char[ strlen( A.name ) + 1 ] ;
	strcpy( name , A.name ) ;
	
	price = A.price ;
	minlvl = A.minlvl ;
	type = A.type ;
	
	return *this ;
	
}

void Item::equals( const Item& A ){
	
	delete[] name ;
	name = new char[ strlen( A.name ) + 1 ] ;
	strcpy( name , A.name ) ;
	
	price = A.price ;
	minlvl = A.minlvl ;
	type = A.type ;
	
}


//Weapon functions

void Weapon::print_all()const{

	cout << get_name() << endl;
	cout << "\nTYPE: Weapon" << endl ;
	cout << "POWER: " << get_dmg() << endl ;
	cout << "HANDS REQUIRED: " << endl ;
	if (isUsed){
		
		cout << "Is currently equipped\n" << endl ;
		
	}else{
		
		cout << "Is not currently equipped\n" << endl ;
		
	}

}

void Weapon::equip( Hero& A ){
	
	if ( A.get_lvl() < get_minlvl() ){
		
		cout << "Your level isn't high enough to use this weapon." << endl ;
		return ;
		
	} 
	
	if ( isUsed ){
		
		cout << "Weapon is already equipped." << endl ;
		return;
	}
	
	if (( A.get_hands() - hands ) > 0 ){
		
		A.set_hands( A.get_hands() - hands ) ;
		A.set_str( A.get_str() + dmg ) ;
		isUsed = 1 ;
		cout << "Equipped the " << get_name() << endl ;
		
	}else{
		
		cout << "Weapon cannot be equippeed. You must have at least " << hands << " free hands." << endl ;
		
	}
	
}

void Weapon::unequip( Hero& A ){
	
	if ( isUsed ){
		
		A.set_hands( A.get_hands() + hands ) ;
		A.set_str( A.get_str() - dmg ) ;
		isUsed = 0 ;
		
	}else{
		
		cout << "Weapon is already unequiped" << endl ;
		
	}
	
}

Weapon& Weapon::operator=( const Weapon& A ){
	
	equals( A ) ;
	dmg = A.dmg ;
	hands = A.hands ;
	isUsed = A.isUsed ; 
	
	return *this ;
	
}



//Armor Functions

void Armor::print_all()const{

	cout << get_name() << endl;
	cout << "\nTYPE: Armor" << endl ;
	cout << "DEF: " << get_def() << endl ;
	cout << "LEVEL: " << get_minlvl() << endl ;
	if (isUsed){
		
		cout << "Is currently equipped\n" << endl ;
		
	}else{
		
		cout << "Is not currently equipped\n" << endl ;
		
	}

}

void Armor::equip( Hero& A ){
	
	if ( A.get_lvl() < get_minlvl() ){
		
		cout << "Your level isn't high enough to equip this armor." << endl ;
		return ;
		
	} 
	
	A.set_amr( def ) ;
	cout << "Wore the " << get_name() << endl ;
	isUsed = 1 ;
	
}

void Armor::unequip( Hero& A ){
	
	A.set_amr( 0.0 ) ;
	cout << "Removed the " << get_name() << endl ;
	isUsed = 0 ;
	
}

Armor& Armor::operator=( const Armor& A ){
	
	equals( A ) ;
	def = A.def ;
	isUsed = A.isUsed ;
	
	return *this ;
	
}

//Potion functions

void Potion::print_all()const{

	cout << get_name() << endl;
	cout << "\nTYPE: Potion" << endl ;
	switch ( stat ){
		
		case 0 :
		
			cout << "STAT: None" << endl ;
			return ;
		
		case 1 :
		 
			cout << "STAT: Strength" << endl ;
			break;
			
		case 2 :
			
			cout << "STAT: Dexterity" << endl ;
			break;
			
		case 3 :
			
			cout << "STAT: Agility" << endl ; ;
			break;
			
		case 4 :
			
			cout << "STAT: Health" << endl ;
			break ;
			
		case 5 :
		
			cout << "STAT: Magic" << endl ;			
			break ;  
			
		default :
			
			cout << "Error02: Invalid potion type requested." << endl ;
				
	}
	
	cout << "ENHANCMENT: " << up << endl ;
	cout << "LEVEL: " << get_minlvl()<< endl ;

}

void Potion::use( Hero& A ){
	
	if ( A.get_lvl() < get_minlvl() ){
		
		cout << "Your level isn't high enough to drink this potion." << endl ;
		return ;
		
	} 
	
	switch ( stat ){
		
		case 0 :
		
			cout << "Can't drink anything out of an empty bottle." << endl ;
			return ;
		
		case 1 :
		 
			A.set_str( A.get_str() + up ) ;
			cout << "Strength increased by " << up << endl ;
			break;
			
		case 2 :
			
			A.set_dex( A.get_dex() + up ) ;
			cout << "Dexterity increased by " << up << endl ;
			break;
			
		case 3 :
			
			A.set_agl( A.get_agl() + up ) ;
			cout << "Agility increased by " << up << endl ;
			break;
			
		case 4 :
			
			A.set_hp( A.get_hp() + up ) ;
			cout << "Healed for " << up << "hit points" << endl ;
			break ;
			
		case 5 :
		
			A.set_mp( A.get_mp() + up ) ;			
			cout << "Recharged for " << up << "magic points" << endl ;
			break ;  
			
		default :
			
			cout << "Error02: Invalid potion type requested." << endl ;
				
	}

//Emptying a bottle could be its own function
	
	set_name( "Empty Bottle" ) ;
	set_price( 10 ) ;
	set_minlvl( 0 ) ;
	stat = 0 ;
	up = 0 ;
	
}


Potion& Potion::operator=( const Potion& A ){
	
	equals( A ) ;
	
	stat = A.stat ;
	up = A.up ;
	
}

//Spell Functions

Spell& Spell::operator=( const Spell& A ){
	
	delete[] name ;
	name = new char[ strlen( A.name) ] ;
	strcpy( name , A.name ) ;
	
	price = A.price ;
	minlvl = A.minlvl ;
	dmg = A.dmg ;
	magic = A.magic ;
	dur = A.dur ;
	
	return *this;
	
}

void Spell::equals( const Spell& A ){
	
	delete[] name ;
	name = new char[ strlen( A.name) ] ;
	strcpy( name , A.name ) ;
	
	price = A.price ;
	minlvl = A.minlvl ;
	dmg = A.dmg ;
	magic = A.magic ;
	dur = A.dur ;

}

void Spell::set_name( const char* n ){
	
	delete[] name ;
	name = new char[ strlen(n) + 1 ] ;
	strcpy( name , n ) ;
	
}

void Spell::set_price( const double p ){
	
	price = p ;
	
}

void Spell::set_minlvl( const int l ){
	
	minlvl = l ;
	
}

void Spell::set_dmg( const range d ){
	
	dmg = d ;
	
}

void Spell::set_magic( const double m ){
	
	magic =  m ;
	
}

void Spell::set_dur( const int i ){
	
	dur = i ;
	
}

//IceSpell functions

IceSpell& IceSpell::operator=( const IceSpell& A ){
	
	equals( A ) ;
	AtkRedu = A.AtkRedu ;
	
	return *this ;
	
}


int IceSpell::use( Hero& A , Monster& B , range& prevAtk ){
	
	if ( A.get_lvl() < get_minlvl()){
		
		cout << "You aren't a high enough level to use this spell yet." << endl ;
		return 0 ;
		
	}
	
	if ( A.get_mp() < get_magic() ){
		
		cout << "You don't have enough magic to use that." << endl ;
		return 0 ;
	}
	
	A.set_mp( A.get_mp() - get_magic() ) ;
	range alteredDamage , spellDamage ; // temp variables for passing the altered damage to the monster and applying the spell's damage to it
	alteredDamage = B.get_dmg() ; 
	spellDamage = get_dmg() ;
	
	prevAtk = B.get_dmg() ; // stores the previous Atk value of the monster
	
	cout << "Dealt " << (B.get_hp() - ( spellDamage.min + (0.01*A.get_dex())*(spellDamage.max - spellDamage.min))) << " damage" ;
	
	B.set_hp( B.get_hp() - ( spellDamage.min + (0.01*A.get_dex())*(spellDamage.max - spellDamage.min) ) ) ; //Minimum dmg guranteed. Maximum damage Achieved only through 100 dexterity
	
	cout << " to " << B.get_name() << " and reduced its damage from " << alteredDamage.min << "-" << alteredDamage.max ;
	
	alteredDamage.max = get_max(alteredDamage.max - AtkRedu , 0.0 ) ;
	alteredDamage.min = get_max(alteredDamage.min - AtkRedu, 0.0 ) ; // Monster Atk reduction complete, now to pass it on to the monster
	B.set_dmg( alteredDamage ) ; //altered dmg now applied to the monster
	
	cout << " to " << alteredDamage.min << "-" << alteredDamage.max << "!" << endl ;
	
	return get_dur() ; //returns the duration for which the debuff will stay applied. After reaching its limit, a different function will be called by the fight itself to restore it
	
}

void IceSpell::print_all()const{
	
	range temp ;
	temp = get_dmg() ;
	cout << get_name() << endl ;
	cout << "Ice Spell\n" << endl ;
	cout << "DAMAGE: " << temp.min << "-" << temp.max << endl ;
	cout << "EFFECT:\nReduces a monster's Attack by " <<  AtkRedu << " for " << get_dur() << "turns." ; 
	cout << "MAGIC COST: " << get_magic() << endl ;
	cout << "PRICE: " <<  get_price() << endl ;
	cout << "MINIMUM LEVEL: " << get_minlvl() << endl ;
	
}

//FireSpell functions

FireSpell& FireSpell::operator=( const FireSpell& A ){
	
	equals( A ) ;
	DefRedu = A.DefRedu ;
	
	return *this ;
	
}

int FireSpell::use( Hero& A , Monster& B , double& prevDef ){
	
	
	
	if ( A.get_lvl() < get_minlvl()){
		
		cout << "You aren't a high enough level to use this spell yet." << endl ;
		return 0 ;
		
	}
	
	if ( A.get_mp() < get_magic() ){
		
		cout << "You don't have enough magic to use that." << endl ;
		return 0 ;
	}
	
	A.set_mp( A.get_mp() - get_magic() ) ;
	double alteredDef ;
	range spellDamage ;
	
	prevDef = B.get_def() ;
	
	cout << "Dealt " << (B.get_hp() - ( spellDamage.min + (0.01*A.get_dex())*(spellDamage.max - spellDamage.min))) << " damage" ;
	
	B.set_hp( B.get_hp() - ( spellDamage.min + (0.01*A.get_dex())*(spellDamage.max - spellDamage.min) ) ) ;
	alteredDef = get_max( B.get_def() - DefRedu , 0.0 ) ;
	B.set_def( alteredDef ) ;
	
	cout << " to " << B.get_name() << " and reduced its defense from " << prevDef << " to " << alteredDef << "!" << endl;
	
}

void FireSpell::print_all()const{
	
	range temp ;
	temp = get_dmg() ;
	cout << get_name() << endl ;
	cout << "Fire Spell\n" << endl ;
	cout << "DAMAGE: " << temp.min << "-" << temp.max << endl ;
	cout << "EFFECT:\nReduces a monster's defense by " << DefRedu << " for " << get_dur() << "turns." ; 
	cout << "MAGIC COST: " << get_magic() << endl ;
	cout << "PRICE: " <<  get_price() << endl ;
	cout << "MINIMUM LEVEL: " << get_minlvl() << endl ;
	
}

//LightningSpell functions

LightningSpell& LightningSpell::operator=( const LightningSpell& A ){
	
	equals( A ) ;
	EvRedu = A.EvRedu ;
	
	return *this ;
	
}

int LightningSpell::use( Hero& A , Monster& B , double& prevAgl ){
	
	if ( A.get_lvl() < get_minlvl()){
		
		cout << "You aren't a high enough level to use this spell yet." << endl ;
		return 0 ;
		
	}
	
	if ( A.get_mp() < get_magic() ){
		
		cout << "You don't have enough magic to use that." << endl ;
		return 0 ;
	}
	
	A.set_mp( A.get_mp() - get_magic() ) ;
	double alteredAgl ;
	range spellDamage ;
	
	prevAgl = B.get_agl() ;
	
	cout << "Dealt " << (B.get_hp() - ( spellDamage.min + (0.01*A.get_dex())*(spellDamage.max - spellDamage.min))) << " damage" ;
	
	B.set_hp( B.get_hp() - ( spellDamage.min + (0.01*A.get_dex())*(spellDamage.max - spellDamage.min) ) ) ;
	alteredAgl = get_max( B.get_agl() - EvRedu , 0.0 ) ;
	B.set_agl( alteredAgl ) ;
	
	cout << " to " << B.get_name() << " and reduced its agility from " << prevAgl << " to " << alteredAgl << "!" << endl;
	
}

void LightningSpell::print_all()const{

	range temp ;
	temp = get_dmg() ;
	cout << get_name() << "\n" ;
	cout << "Lightning Spell\n" << "\n" ;
	cout << "DAMAGE: " << temp.min << "-" << temp.max << "\n" ;
	cout << "EFFECT:\nReduces a monster's agility by " << EvRedu << " for " << get_dur() << "turns.\n" ; 
	cout << "MAGIC COST: " << get_magic() << "\n" ;
	cout << "PRICE: " <<  get_price() << "\n" ;
	cout << "MINIMUM LEVEL: " << get_minlvl() << endl ;
	
}

//Living Functions


void Living::set_hp( const double h ){
	
	hp = get_min( get_max( 0.0 , h ) , max_hp) ;

}

void Living::set_name( const char* n){
	
	delete[] name ;
	name = new char[ strlen(n) + 1 ] ;
	strcpy( name , n ) ;
	
}

void Living::set_lvl( const int l ){
	
	lvl = l ;
	
}

Living& Living::operator=( const Living& A ){
	
	delete[] name ;
	name = new char[ strlen( A.name ) + 1 ] ;
	strcpy( name , A.name ) ;
	hp = A.hp ;
	lvl = A.lvl ;
	
}

//Hero Functions

Hero& Hero::operator=( const Hero& A ){
	
	int i = 0 ;
	
	set_name( A.get_name() ) ;
	set_hp( A.get_hp() ) ;
	set_lvl( A.get_lvl() ) ;
	mp = A.mp ;
	str = A.str ;
	dex = A.dex ;
	agl = A.agl ;
	money = A.money ;
	exp = A.exp ;
	hands = A.hands ;
	amr = A.amr ;
	
	for ( i = 0 ; i < 10 ; i++ ){
		
		delete Inventory[i] ;
		if( A.get_Inv(i).get_type() == 1 ){
			
			Inventory[i] = new Weapon ;
			*Inventory[i] = A.get_Inv(i) ;
			
		}else if( A.get_Inv(i).get_type() == 2 ){
			
			Inventory[i] = new Armor ;
			*Inventory[i] = A.get_Inv(i) ;
			
		}else if( A.get_Inv(i).get_type() == 3 ){
			
			Inventory[i] = new Potion ;
			*Inventory[i]=A.get_Inv(i) ;
			
		}else{
			
			Inventory[i] = new Item ;
			
		}
		
	}
	
	for ( i = 0 ; i < 3 ; i++ ){
		
		delete Tome[i] ;
		if( A.get_Tome(i).get_type() == 1 ){
			
			Tome[i] = new IceSpell ;
			*Tome[i] = A.get_Tome(i) ;
			
		}else if( A.get_Tome(i).get_type() == 2 ){
			
			Tome[i] = new FireSpell ;
			*Tome[i] = A.get_Tome(i) ;
			
		}else if( A.get_Inv(i).get_type() == 3 ){
			
			Tome[i] = new LightningSpell ;
			*Tome[i] = A.get_Tome(i) ;
			
		}else{
			
			Tome[i] = new Spell ;
			
		}
		
	}
	
}



void Hero::set_money( double m ){
	
	money = m ;
	
}

void Hero::set_str( const double s ){
	
	str = get_max( s , 0.0 ) ;
	
}

void Hero::set_mp( const double m ){
	
	mp = get_min( get_max( 0.0 , m ) , max_mp );
	
}
void Hero::set_dex( const double d ){
	
	dex = get_min( 100.0 , get_max( 0.0 , d ) ) ;
	
}

void Hero::set_agl( const double a ){
	
	agl = get_min( 50.0 , get_max( 0.0 , a ) ) ;
	
}



void Hero::set_amr( const double d ){
	
	amr = d ;
	
}

void Hero::set_hands( const int h ){
	
	hands = get_min( 2 , get_max( h , 0 ) ) ;
	
}

void Hero::attack( Monster& A ){
	
	int i1 , j1 ;
	double accuracy ;
	
	i1 = rand() % 100 ;
	j1 = rand() % 100 ;
	
	accuracy = i1 + 0.01 * j1 ;
	
	if (accuracy > A.get_agl()){
	
		A.set_hp( A.get_hp() - get_max( 0.0 , str - A.get_def() ) ) ;
		cout << "Dealt " << get_max( 0.0 , str - A.get_def() )<< " to " << A.get_name() << "!" << endl ;
		
	}else{
		
		cout << A.get_name() << "evaded the attack!" << endl ;
		
	}
}

void Hero::addInv( Item& I ){
	
	int i = 0 ;
	bool isadded = 0 ;
	
	while( ( i < 10 ) && ( isadded == 0 ) ){
		
		if ( strcmp( I.get_name() , "NONE" ) != 0 ){
			
			delete Inventory[i] ;
		
			if( I.get_type() == 1 ){
			
				Inventory[i] = new Weapon ;
				*Inventory[i] = I ;
			
			}else if( I.get_type() == 2 ){
			
				Inventory[i] = new Armor ;
				*Inventory[i] = I ;
			
			}else if( I.get_type() == 3 ){
				
				Inventory[i] = new Potion ;
				*Inventory[i]= I ;
			
			}
			
			isadded = 1 ;
			cout << "Added Item " << I.get_name() << " in slot " << i + 1 << endl ;
			
		}
		
		i++ ;
	}
	
	if ( isadded = 0 ){
		
		cout << "Inventory is full!" << endl ;

	}
	
}

void Hero::removeInv( const int s ){
	
	if ((s < 1) || (s > 10)){
		
		cout << "Error01: Invalid input. Requested Inventory Slot doesnt exist" << endl ;
		
	}else{
		
		delete Tome[ s - 1 ] ;
		Tome[ s - 1 ] = new Spell ;
		cout << " Successfully freed slot " << s << endl ;
	}
	
}

void Hero::addTome( Spell& I ){
	
	int i = 0 ;
	bool isadded = 0 ;
	
	while( ( i < 3 ) && ( isadded == 0 ) ){
		
		if ( strcmp( I.get_name() , "NONE" ) != 0 ){
			
			delete Tome[i] ;
			if( I.get_type() == 1 ){
			
				Tome[i] = new IceSpell ;
				*Tome[i] = I ;
			
			}else if( I.get_type() == 2 ){
			
				Tome[i] = new FireSpell ;
				*Tome[i] = I ;
			
			}else if( I.get_type() == 3 ){
			
				Tome[i] = new LightningSpell ;
				*Tome[i] = I ;
				
			}
		isadded = 1 ;
		cout << "Added Spell " << I.get_name() << " in slot " << i + 1 << endl ;
			
		}
		
		i++ ;
	}
	
	if ( isadded = 0 ){
		
		cout << "Spell Tome is full!" << endl ;

	}
	
}


void Hero::removeTome( const int s ){
	
	if ((s < 1) || (s > 3)){
		
		cout << "Error01: Invalid input. Requested Tome Slot doesnt exist" << endl ;
		
	}else{
		
		delete Tome[ s - 1 ] ;
		Tome[ s - 1 ] = new Spell ; 
		cout << " Successfully freed slot " << s << endl ;
	}
	
}

void Hero::reward( const double e ){ // will be redefined for the Hero subclasses
	
	exp = exp + e ;
	money = money + 0.1 * get_lvl() ;
	if ( exp >= 100 && get_lvl() < 100 ){
		
		cout << "Level Up!" << endl ; 
		exp = exp - 100 ;                       //exp resets and has all leftovers added
		cout<< get_lvl() << "->" ;             
		set_lvl( get_lvl() + 1 ) ;             // Level Up!
		cout << get_lvl() << endl ;
		
		max_hp = max_hp + 0.7 * get_lvl()  ;  //Hp rises more the higher level you are
		max_mp = max_mp + 0.5 * get_lvl()  ;  //so does Magic Power
		
		set_hp(max_hp) ;                     //fully heal with each level up
		set_mp(max_mp) ;
		
		
		set_str( get_str() + 1 ) ; //technically, strength maxes at 100, but weapons and hero classes can make it pass said limit; 
		
		if ( get_dex() < 100 ){
			
			set_dex( get_dex() + 1 ) ;  //Dexterity maxes at 100
			
		}
		
		if ( get_agl() < 50 ){
			
			set_agl( get_agl() + 0.5 ) ; // Agility maxes at 50 (100% chance to evade is kinda over-powered)
			
		}else{
			
			exp = get_min( 100.0 , exp ) ; //If max level has been reached, this ensures that exp doesnt scale infinetely. If it hasn't, this
		                                   //leaves exp as it is	
		}
		
		
	}
	Check_hp() ;
	
}

void Hero::print_all()const{

	cout<< get_name() << "\n\n" 
		<< "CLASS: Hero\n" 
		<< "LEVEL: " << get_lvl() << "(" << exp <<"%)\n"
		<< "HEALTH: " << get_hp() << "\n"
		<< "MAGIC: " << get_mp() << "\n"
		<< "STRENGTH: " << get_str() << "\n"
		<< "DEXTERITY: " << get_dex() << "%\n"
		<< "AGILITY: " << get_agl() << "%\n"
		<< "ARMOR: " << get_amr() << "\n"
		<< "MONEY:" << money << "G\n" << endl ;
		
}

void Hero::buyIt( Item& A ){
	
	if ( money - A.get_price() < 0 ){
	
		cout << "Cant buy this Item. Too expensive." << endl ;
		return ;
		
	}
	
	money = money - A.get_price() ;
	addInv( A ) ;
	
}

void Hero::sellIt( const int i ){
	
	Item A ;
	
	if ( i > 10 || i < 1 ){
		
		cout << "Error01: Invalid input. Requested Inventory Slot doesnt exist" << endl ;
		return ;
		
	}
	if (strcmp(A.get_name(), "NONE") == 0 ){
		
		cout << "Unfortunately, the concept of nothing is not a commodity" << endl ;
		return ;
	}
	
	
	A = *Inventory[ i - 1 ] ;
	
	money = money + A.get_price()/2 ;
	removeInv( i ) ;
	
}


void Hero::buySp( Spell& A ){
	
	if ( money - A.get_price() < 0 ){
	
		cout << "Cant buy this spell. Too expensive." << endl ;
		return ;
		
	}
	
	money = money - A.get_price() ;
	addTome( A ) ;
	
}

void Hero::sellSp( const int i ){
	
	Item A ;
	
	if ( i > 3|| i < 1 ){
		
		cout << "Error01: Invalid input. Requested Tome Slot doesnt exist" << endl ;
		return ;
	}
	
	A = *Inventory[ i - 1 ] ;
	if (strcmp(A.get_name(), "NONE") == 0 ){
		
		cout << "Unfortunately, the concept of nothing is not a commodity" << endl ;
		return ;
		
	}
	
	money = money + A.get_price()/2 ;
	removeInv( i ) ;
	
}

void Hero::print_inv()const{

	int i = 0 ;
	cout << "Inventory: " << "\n" ;
	for( i = 0 ; i < 10 ; i++ ){
		
		cout << i + 1 << ": " << *Inventory[i]->get_name() << endl ;
		
	}

	cout << "\n" << endl ;

}

void Hero::print_tome()const{

	int i = 0 ;
	cout << "Tome: " << "\n" ;
	for( i = 0 ; i < 3 ; i++ ){
		
		cout << i + 1 << ": " << *Tome[i]->get_name() << endl ;
		
	}
	
	cout << "\n" << endl ;
}


void Hero::unequip_all(){
	
	int i ;
	
	for(i = 0 ; i < 10 ; i++ ){
		
		if ((Inventory[i]->get_type() ==2) || (Inventory[i]->get_type() == 1)){
			
			Inventory[i]->unequip(*this) ;
			
		}
		
	}
	
}

void Hero::Equip_Use( const int i ){
	
	if (Inventory[i]->get_type()==3){
		
		Inventory[i]->use(*this) ;
		
	}else if ((Inventory[i]->get_type()==2)||(Inventory[i]->get_type()==1)){
		
		Inventory[i]->equip(*this) ;
		
	}else{
		
		cout << "Can't do much with nothing..." << endl ;
		
	}
}

void Hero::Use_Spell( const int i , Monster& A , range& Prev ){
	
	Tome[i]->use( *this , A , Prev ) ;
	
}

void Hero::Use_Spell( const int i , Monster& A , double& Prev ){
	
	Tome[i]->use( *this , A , Prev ) ;
	
}

void Hero::Check_hp(){
	
	if (get_hp() == 0 ){
		
		set_hp( max_hp/2.0 ) ;
		
	}
	
}

//Warrior, Sorcerer and Paladin functions

void Warrior::reward( const double e ){ //
	
	exp = exp + e ;
	money = money + 0.1 * get_lvl() ;
	if ( exp >= 100 && get_lvl() < 100 ){
		
		cout << "Level Up!" << endl ; 
		exp = exp - 100 ;                       //exp resets and has all leftovers added
		cout<< get_lvl() << "->" ;             
		set_lvl( get_lvl() + 1 ) ;             // Level Up!
		cout << get_lvl() << endl ;
		
		max_hp = max_hp + 0.7 * get_lvl()  ;  //Hp rises more the higher level you are
		max_mp = max_mp + 0.5 * get_lvl()  ;  //so does Magic Power
		
		set_hp(max_hp) ;                     //fully heal with each level up
		set_mp(max_mp) ;
		
		set_str( get_str() + 1.2 ) ; // At level 100, Warriors have 21 more damage than regular Heroes
		
		if ( get_dex() < 100 ){
			
			set_dex( get_dex() + 1 ) ;  //Dexterity maxes at 100
			
		}
		
		if ( get_agl() < 50 ){
			
			set_agl( get_min(get_agl() + 1 , 50.0 ) ) ; // Warriors reach maximum Agility on lvl 50 , twice as fast as other heroes
			
		}else{
			
			exp = get_min( 100.0 , exp ) ; //If max level has been reached, this ensures that exp doesnt scale infinetely. If it hasn't, this
		                                   //leaves exp as it is	
		}
		
		
	}
	
	Check_hp() ;
	
}

void Warrior::print_all()const{

	cout<< get_name() << "\n\n" 
		<< "CLASS: Warrior\n" 
		<< "LEVEL: " << get_lvl() << "(" << exp <<"%)\n"
		<< "HEALTH: " << get_hp() << "\n"
		<< "MAGIC: " << get_mp() << "\n"
		<< "STRENGTH: " << get_str() << "\n"
		<< "DEXTERITY: " << get_dex() << "%\n"
		<< "AGILITY: " << get_agl() << "%\n"
		<< "ARMOR: " << get_amr() << "\n"
		<< "MONEY:" << money << "G\n" << endl ;
		
}

void Sorcerer::reward( const double e ){ 
	
	exp = exp + e ;
	money = money + 0.1 * get_lvl() ;
	if ( exp >= 100 && get_lvl() < 100 ){
		
		cout << "Level Up!" << "\n" ; 
		exp = exp - 100 ;                       //exp resets and has all leftovers added
		cout<< get_lvl() << "->" ;             
		set_lvl( get_lvl() + 1 ) ;             // Level Up!
		cout << get_lvl() << endl ;
		
		max_hp = max_hp + 0.7 * get_lvl()  ;  //Hp rises more the higher level you are
		max_mp = max_mp + 0.5 * get_lvl()  ;  //so does Magic Power
		
		set_hp(max_hp) ;                     //fully heal with each level up
		set_mp(max_mp) ;
		
		set_str( get_str() + 1 ) ; //technically, strength maxes at 100, but weapons and hero classes can make it pass said limit; 
		
		if ( get_dex() < 100 ){
			
			set_dex( get_min( get_dex() + 2.0 , 100.0 ) ) ;  // Sorcerers max dexterity at lvl 50
			
		}
		
		if ( get_agl() < 50 ){
			
			set_agl( get_min( get_agl() + 1 , 50.0 ) ) ; // Sorcerers max dexterity at lvl 50
			
		}else{
			
			exp = get_min( 100.0 , exp ) ; //If max level has been reached, this ensures that exp doesnt scale infinetely. If it hasn't, this
		                                   //leaves exp as it is	
		}
		
		
	}
	
	Check_hp() ;
	
}

void Sorcerer::print_all()const{

		cout<< get_name() << "\n\n" 
		<< "CLASS: Paladin\n" 
		<< "LEVEL: " << get_lvl() << "(" << exp <<"%)\n"
		<< "HEALTH: " << get_hp() << "\n"
		<< "MAGIC: " << get_mp() << "\n"
		<< "STRENGTH: " << get_str() << "\n"
		<< "DEXTERITY: " << get_dex() << "%\n"
		<< "AGILITY: " << get_agl() << "%\n"
		<< "ARMOR: " << get_amr() << "\n"
		<< "MONEY:" << money << "G\n" << endl ;
		
}

void Paladin::reward( const double e ){ 
	
	exp = exp + e ;
	money = money + 0.1 * get_lvl() ;
	if ( exp >= 100 && get_lvl() < 100 ){
		
		cout << "Level Up!" << endl ; 
		exp = exp - 100 ;                       //exp resets and has all leftovers added
		cout<< get_lvl() << "->" ;             
		set_lvl( get_lvl() + 1 ) ;             // Level Up!
		cout << get_lvl() << endl ;
		
		max_hp = max_hp + 0.7 * get_lvl()  ;  //Hp rises more the higher level you are
		max_mp = max_mp + 0.5 * get_lvl()  ;  //so does Magic Power
		
		set_hp(max_hp) ;                     //fully heal with each level up
		set_mp(max_mp) ;
		
		set_str( get_str() + 1.2 ) ; //At level 100, Paladins have 21 more damage than regular Heroes
		
		if ( get_dex() < 100 ){
			
			set_dex( get_min( get_dex() + 2.0 , 100.0 ) ) ;  // Paladins max dexterity at lvl 50
			
		}
		
		if ( get_agl() < 50 ){
			
			set_agl( get_agl() + 0.5 ) ; // Agility reaches its 50% cap at lvl 100
			
		}else{
			
			exp = get_min( 100.0 , exp ) ; //If max level has been reached, this ensures that exp doesnt scale infinetely. If it hasn't, this
		                                   //leaves exp as it is	
		}
		
		
	}
	
	Check_hp() ;
	
}

void Paladin::print_all()const{

	cout<< get_name() << "\n\n" 
		<< "CLASS: Paladin\n" 
		<< "LEVEL: " << get_lvl() << "(" << exp <<"%)\n"
		<< "HEALTH: " << get_hp() << "\n"
		<< "MAGIC: " << get_mp() << "\n"
		<< "STRENGTH: " << get_str() << "\n"
		<< "DEXTERITY: " << get_dex() << "%\n"
		<< "AGILITY: " << get_agl() << "%\n"
		<< "ARMOR: " << get_amr() << "\n"
		<< "MONEY:" << money << "G\n" << endl ;
		
}

//Monster Functions

Monster& Monster::operator=( const Monster& A ){
	
	set_name( A.get_name() ) ;
	set_hp( A.get_hp() ) ;
	set_lvl( A.get_lvl() ) ;
	dmg = A.dmg ;
	def = A.def ;
	agl = A.agl ;
	
	return *this ;
	
}

void Monster::set_dmg( const range d ){
	
	dmg.max = d.max ;
	dmg.min = d.min ;
	
}

void Monster::set_def( const double d ){
	
	def = d ;
	
}

void Monster::set_agl( const double a ){
	
	agl = a ;
	
}

void Monster::attack( Hero& A ){
	
	int i , j , i1 , j1 ;
	double damage , accuracy ;
	
	i = rand() % int(dmg.min) + int(dmg.max - dmg.min) ;
	j = rand() % 100 ;
	damage = i + 0.01*j ;
	
	i1 = rand() % 100 ;
	j1 = rand() % 100 ;
	
	accuracy = i1 + 0.01 * j1 ;
	
	if (accuracy > A.get_agl()){
	
		A.set_hp( A.get_hp() - get_max( 0.0 , damage - A.get_amr() ) ) ;
		cout << get_name() << " dealt " << get_max( 0.0 , damage - A.get_amr() ) << " damage to " << A.get_name()<< "!" << endl ;
		
	}else{
		
		cout << A.get_name() << " eveded " << get_name() << " 's attack!" << endl ;
		
	}
}

void Monster::print_all()const{

	cout<< get_name() << "\n\n"
		<< "TYPE: Monster\n"
		<< "LEVEL: " << get_lvl() << "\n"
		<< "HEALTH: " << get_hp() << "\n"
		<< "DAMAGE: " << dmg.min << "-" << dmg.max << "\n"
		<< "DEFENSE: " << def << "\n"
		<< "AGILITY: " << agl << "\n\n" << endl ;

}

void Dragon::print_all()const{

	cout<< get_name() << "\n\n"
		<< "TYPE: Dragon\n"
		<< "LEVEL: " << get_lvl() << "\n"
		<< "HEALTH: " << get_hp() << "\n"
		<< "DAMAGE: " << dmg.min << "-" << dmg.max << "\n"
		<< "DEFENSE: " << def << "\n"
		<< "AGILITY: " << agl << "\n\n" << endl ;


}

void Exoskeleton::print_all()const{

	cout<< get_name() << "\n\n"
		<< "TYPE: Exoskeleton\n"
		<< "LEVEL: " << get_lvl() << "\n"
		<< "HEALTH: " << get_hp() << "\n"
		<< "DAMAGE: " << dmg.min << "-" << dmg.max << "\n"
		<< "DEFENSE: " << def << "\n"
		<< "AGILITY: " << agl << "\n\n" << endl ;


}

void Spirit::print_all()const{

	cout<< get_name() << "\n\n"
		<< "TYPE: Spirit\n"
		<< "LEVEL: " << get_lvl() << "\n"
		<< "HEALTH: " << get_hp() << "\n"
		<< "DAMAGE: " << dmg.min << "-" << dmg.max << "\n"
		<< "DEFENSE: " << def << "\n"
		<< "AGILITY: " << agl << "\n\n" << endl ;


}

//Grid functions

void Grid::reset(){
	
	curcord.x = 3 ;
	curcord.y = 3 ;
	
}
	
	
int Grid::move( const char m ){ //it returns 1 when the players is at the market, 2 if the player didnt move, 0 if the players successfully moved or 9 if input was wrong
	
	int i = 0 ;
	coordinates direction = curcord ;
	
	if ( m == 's' ){
		
		direction.y = direction.y + 1 ;
		
		if ( direction.y > 4 ){ //check if player is attempting to move outside the map
			
			cout << "Cannot move outside the Map!" << endl ;
			return 2 ;
			
		}
		
		for ( i = 0 ; i < 4 ; i++ ){              //for every non accessible block
			
			if ( (direction.x == nonacc[i].x) && ( direction.y == nonacc[i].y )){		  //check if its in the way	
				
				cout << "You can't traverse that terrain" << endl ;
				return 2 ;
				
			}
			
		}
		
		if (( direction.x == market.x ) && ( direction.y == market.y)){ //Check if player moved to the Market
			
			cout << "Welcome to the Market!" << endl ;  //In the main function, after this, 
														//remember to ask the player if he wants
														//to buy or sell, then either print a
														//list of available items and spells
														//or a list of his Inventory and Tome
			return 1 ;  //The players position doesn't change. After quitting the market, it remains as
						//it previously was											
			
		}
		
		curcord = direction ;
		return 0 ;
		
	}
	
	if ( m == 'w' ){
		
		direction.y = direction.y - 1 ;
		
		if ( direction.y < 0 ){ //check if player is attempting to move outside the map
			
			cout << "Cannot move outside the Map!" << endl ;
			return 2 ;
			
		}
		
		for ( i = 0 ; i < 4 ; i++ ){              //for every non accessible block
			
			if ( (direction.x == nonacc[i].x) && ( direction.y == nonacc[i].y )){		  //check if its in the way	
				
				cout << "You can't traverse that terrain" << endl ;
				return 2 ;
			}
			
		}
		
		if (( direction.x == market.x ) && ( direction.y == market.y)){ //Check if player moved to the Market
			
			cout << "Welcome to the Market!" << endl ;  //In the main function, after this, 
														//remember to ask the player if he wants
														//to buy or sell, then either print a
														//list of available items and spells
														//or a list of his Inventory and Tome
			return 1 ;  //The players position doesn't change. After quitting the market, it remains as
						//it previously was											
			
		}
		
		curcord = direction ;
		return 0 ;
		
	}
	
	if ( m == 'd' ){
		
		direction.x = direction.x + 1 ;
		
		if ( direction.x > 4 ){ //check if player is attempting to move outside the map
			
			cout << "Cannot move outside the Map!" << endl ;
			return 2 ;
			
		}
		
		for ( i = 0 ; i < 4 ; i++ ){              //for every non accessible block
			
			if ( (direction.x == nonacc[i].x) && ( direction.y == nonacc[i].y )){		  //check if its in the way	
				
				cout << "You can't traverse that terrain" << endl ;
				return 2 ;
			}
			
		}
		
		if (( direction.x == market.x ) && ( direction.y == market.y)){ //Check if player moved to the Market
			
			cout << "Welcome to the Market!" << endl ;  //In the main function, after this, 
														//remember to ask the player if he wants
														//to buy or sell, then either print a
														//list of available items and spells
														//or a list of his Inventory and Tome
			return 1 ;  //The players position doesn't change. After quitting the market, it remains as
						//it previously was											
			
		}
	}
	
	if ( m == 'a' ){
		
		direction.x = direction.x - 1 ;
		
		if ( direction.x < 0 ){ //check if player is attempting to move outside the map
			
			cout << "Cannot move outside the Map!" << endl ;
			return 2 ;
			
		}
		
		for ( i = 0 ; i < 4 ; i++ ){              //for every non accessible block
			
			if ( (direction.x == nonacc[i].x) && ( direction.y == nonacc[i].y )){		  //check if its in the way	
				
				cout << "You can't traverse that terrain" << endl ;
				return 2 ;
			}
			
		}
		
		if (( direction.x == market.x ) && ( direction.y == market.y)){ //Check if player moved to the Market
			
			cout << "Welcome to the Market!" << endl ;  //In the main function, after this, 
														//remember to ask the player if he wants
														//to buy or sell, then either print a
														//list of available items and spells
														//or a list of his Inventory and Tome
			return 1 ;  //The players position doesn't change. After quitting the market, it remains as
						//it previously was											
			
		}
	}
		
	curcord = direction ;
	return 0 ;
		
	
	
	cout << "Error04: Invalid Input into the controller function" << endl ;
	
	return 9 ;
	
}

void Grid::print_Map()const{

	int i = 0 , j = 0 , l = 0 ;
	bool isPrinted = 0 , isNa = 0 ;
	
	for( i = 0 ; i < 5 ; i++ ){                                                  //traversing line
		
		for( j = 0 ; j < 5 ; j++ ){                                              //traversing collumn

			isPrinted = 0 ;
			isNa = 0 ;
			for( l = 0 ; l < 4 ; l++ ){                                      //for every non-accessible block
				
				if ( ( j == nonacc[l].x) && ( i == nonacc[l].y) && ( isPrinted == 0 ) ){    //If coords are a non accessible block			
				
					isNa = 1 ;
			    		
				}
			}
			if ( j == market.x && i == market.y ){                               //if its a market
			
				cout << "M" ;						                             //Print out the market symbol
				isPrinted = 1 ;
				
			}else if( j == curcord.x && i == curcord.y){						 //else if its the players position
				
				cout << "P" ;													 //Print out a party symbol
				isPrinted = 1 ;
	
			}else if( isNa == 1 ){                                           //if it wasnt
			
				cout << "+" ;                                            //print a rock :3
			    isPrinted = 1 ;
				
			}else if(isPrinted == 0){                                                               //If it wasnt that either            
				
				cout << "|" ;                                                    //print a line
				isPrinted = 1 ;
			}
		}
		
		cout << "\n" ;
		
	}
	
	cout << "\n" << endl ;
	
}


//battle function


double battle(Hero *Party[] , int size ){

					
	int rgn1 = 0 , i = 0 , a = 0 , l = 0 , j = 0 ;
	bool hasWon = 0 , hasLost = 0 ;
	double prevDef, prevAgl ;
	range prevAtk ;
	
	Monster *enemy = { new Monster , } ;
								
					
		
	rgn1 =  rand() % 3 ;
	
	if(rgn1 == 0 ){
			
		delete enemy ;
		enemy = new Dragon( "Wyvern" , Party[0]->get_lvl() ) ;
							
	}else if(rgn1 == 1){
			
		delete enemy ;
		enemy = new Exoskeleton("Golem" , Party[0]->get_lvl() ) ;
			
	}else{
			
		delete enemy ;
		enemy = new Spirit("Ghast" , Party[0]->get_lvl() ) ;
			
	}
		
		
	
	while( (hasWon == 0) && (hasLost == 0 ) ){
		
		i = 0 ;
		enemy->set_dmg(prevAtk) ;
		enemy->set_def(prevDef) ;
		enemy->set_agl(prevAgl) ;
		
		while ( i < size && hasWon == 0 ){
			
			
			if(Party[i]->get_hp() > 0 ){
			
				cout<< Party[i]->get_name() << "'s turn!\n"
					<< "What will they do?\n"
					<< "1. Attack\n"
					<< "2. Use Spell\n" << endl ;
								
				cin >> a ;
				
				if ( a == 1 ){
					
					Party[i]->attack(*enemy) ;
					
				}else if( a == 2){
			
					cout<< "Which Spell?\n" ;
					Party[i]->print_tome() ;
					cin >> a ;
				
					if( strcmp(Party[i]->get_Tome(a-1).get_name() , "NONE" ) !=0 ){
					
						cout << "Which Monster?\n" ; 
				
						for( i = 0 ; i < rgn1 ; i++ ){
					
							cout << i + 1 << ". " << enemy->get_name() << "\n" ;
						
						}
				
						cin >> a ;
									
						if (Party[i]->get_Tome(a-1).get_type() == 1){
							
							Party[i]->Use_Spell( a-1 , *enemy , prevAtk ) ;
					
						}else if(Party[i]->get_Tome(a-1).get_type() == 2){
						
							Party[i]->Use_Spell( a-1 , *enemy , prevDef ) ;
										
						}else{
	
							Party[i]->Use_Spell( a-1 , *enemy , prevAgl ) ;
						
						}
					
					
					
					}else{
					
						cout << "Can't use that!" << endl ;
					
					}
			
				}
			
								
				
				if( enemy->get_hp() == 0 ){
										
					hasWon = 1 ;
									
					
				}
				
								
			
							
			
				i++ ;
			}
		}
		
						
			
		if(enemy->get_hp() > 0){
			
			cout << "Monster's turn to attack!" << endl ;
			
			rgn1 = rand() % size ;				
			enemy->attack( *Party[rgn1] ) ;
							
		}
							
		l = 0 ;
		for( j = 0 ; j < size ; j++ ){
				
			if( Party[j]->get_hp() == 0 ){
					
				cout<< Party[j]->get_name() << " has fallen!" << endl ;
				l++ ;
					
			}else{
				
				cout << Party[j]->get_name() << " keeps fighting!" << endl ;
				
			}
				
		}
			
		if( l == size ){
				
			hasLost = 1 ;
				
		} 
						
		
		for( j = 0 ; j < size ; j++ ){
			
			if( Party[j]->get_hp() > 0){
			
				Party[j]->restore_hp() ;
				Party[j]->restore_mp() ;
								
			}
			
			
		}
						
		
		if( enemy->get_hp() > 0){
								
			enemy->restore_hp() ;
			enemy->set_dmg(prevAtk) ;
			enemy->set_def(prevDef) ;	
			enemy->set_agl(prevAgl) ;
		}
		
		
		
		
	}
	
	if (hasLost){
		
		cout << "You have lost the battle..." << endl ;
		return 0 ;
		
	}else if(hasWon){
		
		cout << "You have won the battle!" << endl ;
		return 101 ;
		
	}
	
	delete enemy ;
	
					
					
					
					
					
					
					
					
}
					
				
	




















//main function

int main(){
	
	int i = 0 , s = 0 , l = 0 , j = 0 , size = 0 , LeadPosition = 0 ;
	char a = 'l';
	int battle_check = 0 , move_check = 0 ;
	double exp ;
	
	coordinates na , mark ;
	mark.x = 3 ;
	mark.y = 4 ;
	na.x = 1 ;
	na.y = 2 ;
	Grid Map( na , na , na , na , mark  ) ;
	Map.print_Map() ; 
	
	srand (time(NULL)) ;
	
	Item *ShopIt[30] = {
	//				name				     price  lvl  type   dmg  hands bool
	new Weapon( "Commonly Large Stick"      , 5    ,  0 ,  1  ,   1 ,  1 ) ,        //1
	new Weapon( "Wooden Sword"              , 10   ,  1 ,  1  ,   5 ,  1 ) ,        //2
	new Weapon( "Iron Sword"                , 50   , 10 ,  1  ,  15 ,  1 ) ,        //3
	new Weapon( "Enchanted Sword"           , 150  , 40 ,  1  ,  60 ,  1 ) ,        //4
	new Weapon( "God-Forge Sword"           , 300  , 70 ,  1  ,  90 ,  1 ) ,        //5
	new Weapon( "Uncommonly Large Stick"    , 7    ,  0 ,  1  , 1.5 ,  2 ) ,        //6
	new Weapon( "Wooden Longsword"          , 10   ,  1 ,  1  ,   4 ,  2 ) ,        //7
	new Weapon( "Iron Longsword"            , 70   , 10 ,  1  ,  25 ,  2 ) ,        //8
	new Weapon( "Enchanted Longsword"       , 180  , 40 ,  1  ,  80 ,  2 ) ,        //9
	new Weapon( "God-Forge Longsword"       , 350  , 70 ,  1  , 120 ,  2 ) ,        //10
	new Weapon( "3 Levitating Sticks"       , 10   ,  0 ,  1  ,   5 ,  0 ) ,        //11
	new Weapon( "Kanshou and Bakuya"        , 300  , 75 ,  1  , 150 ,  2 ) ,        //12
	new Weapon( "Gaster Blaster"            , 400  , 20 ,  1  ,  40 ,  0 ) ,        //13	
	new Weapon( "Death Fire Grasp"          , 3000 , 90 ,  1  , 121 ,  0 ) ,        //14
	new Weapon( "Forge Masters Hammer"      , 300  , 80 ,  1  , 180 ,  2 ) ,        //15
	new Weapon( "Sword of Evil's' Bane"     , 400  , 90 ,  1  , 150 ,  1 ) ,        //16
	new Weapon( "A Friendly Oompa Loompa"   , 100  , 10 ,  1  ,  30 ,  0 ) ,        //17
	new Weapon( "Diamond Bonker"            , 200  , 75 ,  1  , 100 ,  1 ) ,        //18
	new Weapon( "Diatrexon Aster Lokhe"     , 300  , 85 ,  1  , 134 ,  1 ) ,        //19
	new Weapon( "The Power of Frienship :D" ,    0 , 0  ,  1  , 999999999999 , 0 ) , //20
	
	//            name                        price  lvl  type  def bool
	new Armor( "Wooden Armor"               ,  5  ,  1  ,  2  , 10 ) ,               //21
	new Armor( "Iron Armor"                 ,  10 ,  10 ,  2  , 15 ) ,               //22    
	new Armor( "Enchanted Armor"            ,  50 ,  40 ,  2  , 27 ) ,               //23      
	new Armor( "God-Forge Armor"            , 150 ,  70 ,  2  , 40 ) ,               //24       
	new Armor( "Armor of the Sun Crest"     ,  70 ,  20 ,  2  , 17 ) ,               //25     
	                                                                                         
	//             name                       price lvl   type  stat up 
	new Potion( "Health Potion"             ,   4 ,  0  ,  3  ,  4 , 50  ) ,             //26      
	new Potion( "Magic Potion"              ,   4 ,  0  ,  3  ,  5 , 50  ) ,             //27      
	new Potion( "Strength Potion"           ,   4 ,  0  ,  3  ,  1 ,  5  ) ,             //28                    
	new Potion( "Dexterity Potion"          ,   4 ,  0  ,  3  ,  2 ,  1  ) ,             //29    
	new Potion( "Agility Potion"            ,   4 ,  0  ,  3  ,  3 , 0.1 )               //30        
	
	};
	
	Spell *ShopSp[10] = {
	//                name                 price  level  maxdmg  mindmg  cost  dur   redu
	new IceSpell( "A very bad joke"      ,  10  ,    2  ,  60  ,   10  ,  5  ,  1  ,  10  ) ,  //1
	new IceSpell( "Icicle Toss"          ,  40  ,   20  ,  150 ,   40  ,  10 ,  1  ,  20  ) ,  //2
	new IceSpell( "Blizzard"             ,  80  ,   80  ,  400 ,   60  ,  20 ,  1  ,  50  ) ,  //3
	
	//                name                 price  level  maxdmg  mindmg  cost  dur   redu
	new FireSpell( "A very nasty insult" ,  10  ,    2  ,  60   ,  10  ,  5  ,  1   , 10  ) , //4
	new FireSpell( "Fireball"            ,  40  ,   20  ,  150  ,  40  ,  10 ,  1   , 20  ) , //5
	new FireSpell( "Meteor Shower"       ,  80  ,   80  ,  400  ,  60  ,  20 ,  1   , 50  ) , //6
	
	//                           name                   price  level  maxdmg  mindmg  cost  dur   redu
	new LightningSpell("A very skillful distraction"  ,  10  ,  2  ,   60   ,   10  ,  5  ,  1  ,  10  ) , //7
	new LightningSpell("Shock Wave"                   ,  40  ,  20 ,   150  ,   40  ,  10 ,  1  ,  15  ) , //8
	new LightningSpell("Thunderstorm"                 ,  80  ,  80 ,   400  ,   60  ,  20 ,  1  ,  30  ) , //9
	
	new LightningSpell("Back-Street Boys concert"     ,  1   ,  1  ,  99999 ,  9999 ,  1  ,  1  ,  50  )  , //10
	
	} ;
	
	Hero *Characters[4]{
		//         new
		new Hero("Karna") ,
		new Warrior("Medb") ,
		new Sorcerer("Medea") ,
		new Paladin("Arthur") ,
	
	} ;
	
	Hero *Party[3]{
	
		new Hero ,
		new Hero ,
		new Hero 
	
	} ;
	

	
	Hero CurrentLead ;
	
	
	
	
	
	
	cout<< "Choose a Character!\n" ;
	for( i = 0 ; i < 4 ; i++ ){
		
		cout << i + 1 << ". " << Characters[i]->get_name() << "\n" ;
		
	}
	
	i = 0 ;
	
	while ( (a != 'q') && (a!='y') && i < 3 ){
		
		
		cin >> s ;
		if( (s > 0) && ( s < 5 ) ){
			
			if ( s == 2 ){
				
				delete Party[i] ;
				Party[i] = new Warrior ;
				
			}
			if ( s == 3 ){
				
				delete Party[i] ;
				Party[i] = new Sorcerer ;
				
			}
			
			if ( s == 4 ){
				
				delete Party[i] ;
				Party[i] = new Paladin ;
				
			}
			
			
			*Party[i] = *Characters[ s - 1 ] ;
			cout << "Added " << Party[i]->get_name() << " to the party in slot " << i + 1 << "." << endl ;
			i++ ;
			
		}
		
		if( i < 3 ){
			
			cout << "Stop adding players? y/n" << endl ;
			cin >> a ;
			
		}else{
			
			cout << "Party is full!" << endl ;
			
		}
		
	}
	
	size = i  ;
	cout << "Party size is " << size << "." << endl ;
	
	CurrentLead = *Party[0] ;
	LeadPosition = 0 ;
	
	cout << "Playing with " << CurrentLead.get_name() << endl ;
	
	cout << "Choose and action:\n" 
		 << "WASD: Move\n"  
		 << "I: Check Inventory\n"
		 << "T: Check Tome\n"
		 << "H: Check Hero\n"
		 << "Z: Switch Hero\n" 
		 << "Q: Quit Game\n"<< endl ;
		 
	while (( a != 'q') && (a != 'Q')){
		
		cin >> a ;
		
		if ( (a =='w') || (a =='d') || (a =='a') || (a =='s') ){
			
			move_check = Map.move( a ) ;
			Map.print_Map() ;
			
			if( move_check == 0 ){		
			
				battle_check = rand() % 6 + 1 ;
				if( battle_check == 1 ){
				
				
				
				
				
				
					cout << "A battle has begun!" << endl ;
					
					exp = battle( Party , size ) ;
					if ( exp== 0 ){
						
						for ( i = 0 ; i < size ; i++){
							
							Party[i]->punish() ;
							
						}
						
					}else{
						
						for ( i = 0 ; i < size ; i++){
							
							Party[i]->reward(exp) ;
							
						}
						
					}
				}
					
			}else if ( move_check == 1 ){
				
				cout<< "What would you like to do?\n" 
					<< "1. Buy Items\n"
					<< "2. Buy Spells\n"
					<< "3. Sell Items\n"
					<< "4. Sell Spell\n" 					
					<< "5. Quit" << endl ;
					
				cin >> s ;
					
				switch(s){
						
					case 1 :
							
						for( i = 0 ; i < 30 ; i++){
							
							cout << i + 1 << ". " << ShopIt[i]->get_name() << "\n" ;
							
						}
						
						cout << "Choose an Item.\n" ;
						
						cin >> s ;
						ShopIt[s-1]->print_all() ;
						cout << "This Item?y/n\n" ;
						cin >> a;
						if (a == 'y'){
							
							Party[LeadPosition]->buyIt( *ShopIt[s-1] ) ;
							
						}
						
						break ;
						
					case 2 :
							
						for( i = 0 ; i < 10 ; i++){
							
							cout << i + 1 << ". " << ShopSp[i]->get_name() << "\n" ;
							
						}
					
						cout << "Choose a Spell.\n" ;
						
						cin >> s ;
						ShopSp[s-1]->print_all() ;
						cout << "This Spell?y/n\n" ;
						cin >> a ;
						if (a == 'y'){
							
							Party[LeadPosition]->buySp( *ShopSp[s-1] ) ;
							
						}
						
						break ;
					
					case 3 :
						break;
					
											
						Party[LeadPosition]->print_inv() ;
						cout << "Which Item?\n" ;
						
						cin >> s ;
						Party[LeadPosition]->get_Inv(s-1).print_all() ;
						cout <<"Sell this Item? y/n\n" ;
						cin >> a ;
						if (a == 'y'){
							
							Party[LeadPosition]->sellIt(s) ;
							
						}
						
						break ;
						
					case 4 :
											
						Party[LeadPosition]->print_tome() ;
						cout << "Which Spell?\n" ;
						
						cin >> s ;
						Party[LeadPosition]->get_Tome(s-1).print_all() ;
						cout <<"Sell this Spell?? y/n\n" ;
						cin >> a ;
						if (a == 'y'){
							
							Party[LeadPosition]->sellSp(s) ;
							
						}
						
						break ;
					
					default :
						
						cout<<"Left the market." << endl ;
						
					}
					
			}
					
					
		}else if( ( a == 'h') || ( a == 'H') ){
			
			Party[LeadPosition]->print_all() ;
			
		}else if(( a == 'z') || ( a == 'Z')){
			
			for( i = 0 ; i < 3 ; i++){
				
				cout << i+1 << ". " << Party[i]->get_name() << endl ;
				
			}
			
			cout << "Which one should be the next leader?" << endl ;
			cin >> s ;
			if ( s>1 && s<4 ){
				
				LeadPosition = s- 1 ;
				CurrentLead = *Party[s-1] ;
				cout << Party[LeadPosition]->get_name() << " now leads the party!" ;
				
			}
			
			
			
		}else if(( a == 'i') || (a == 'I' )){
			
			Party[LeadPosition]->print_inv() ;
			cout<< "What would you like to do?\n" 
				<<"1. Equip/Use Item"
				<<"2. Unequip All Items"
				<<"3. Quit" ;
			
			cin >> s ;
			if(s == 1){
				
				cout << "Which Item?\n" ;
				cin >> s ;
				Party[LeadPosition]->Equip_Use(s-1) ;
				
			}else if( s == 2 ){
				
				Party[LeadPosition]->unequip_all() ;
				
			}
			
		}else if(( a == 't') || (a == 'T')){
			
			Party[LeadPosition]->print_tome() ;
			
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	for( i = 0 ; i < 30 ; i++ ){
		
		delete ShopIt[i] ;
		
	}
	
	for ( i = 0 ; i < 10 ; i++ ){
		
		delete ShopSp[i] ;
		
	}
	
	for ( i = 0 ; i < 4 ; i++ ){
		
		delete Characters[i] ;
		
	}
	
	for ( i = 0 ; i < 3 ; i++ ){
		
		delete Party[i] ;
		
	}
	
	
	return 0 ;
	
}


















