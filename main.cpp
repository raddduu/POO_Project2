///acest cod simuleaza baza de date a unei agentii de imobiliare care ofera cladiri cu scop de resedinta, sediu de firma sau ambele, tratand problema
///persoanelor al caror sediu de firma coincide cu sediul social prin mostenirea in diamant disponibila in C++!
#include <iostream>
#include <stdlib.h>

using namespace std;

class building{
public:
    building(int,string);
    building(const building&);
    virtual~building();
    building operator = (building);
    friend istream& operator >> (istream&, building&);
    friend ostream& operator << (ostream&, building&);
    friend bool operator == (building, building);
    void display();
    static double get_price_per_sqm();
    int get_area();
    void set_area(int);
    void set_city(string);
    static void set_price_per_sqm(double);
    virtual void type();
private:
    static double price_per_sqm;
    int area;
    string city;
};

double building::price_per_sqm = 0.3;

void building::set_price_per_sqm(double new_price)
{
    price_per_sqm = new_price;
}

building::building(int a = 0, string l = "NULL_CITY"):area(a),city(l){}

building::building(const building& b)
{
    area = b.area;
    city = b.city;
}

building::~building(){}

building building:: operator = (building b)
{
    area = b.area;
    city = b.city;
    return (*this);
}

istream& operator >> (istream& in, building& b)
{
    in>>b.area>>b.city;
    return in;
}

ostream& operator << (ostream& out, building& b)
{
    out<<"The building in the city of "<<b.city<<" has a surface of "<<b.area<<" m^2\n";
    return out;
}

bool operator == (building b1, building b2)
{
    return (b1.area==b2.area)*(b1.city==b2.city);
}

void building::display()
{
    cout<<"The building at city "<<city<<" has a surface of "<<area<<" m^2";
}

double building::get_price_per_sqm()
{
    return price_per_sqm;
}

int building::get_area()
{
    return area;
}

void building::set_area(int new_area)
{
    area = new_area;
}

void building::set_city(string new_city)
{
    city = new_city;
}

void building::type()
{
    cout<<"building\n";
}

class domicile: public virtual building{
public:
    domicile(int,string,int,int,string);
    domicile(const domicile&);
    virtual~domicile();
    domicile operator = (domicile&);
    friend istream& operator >> (istream&, domicile&);
    friend ostream& operator << (ostream&, domicile&);
    friend bool operator == (domicile, domicile);
    void display();
    double payment_per_rezident();
    void type();
private:
    int number_of_rezidents,rooms_number;
    string domicile_type;

};

domicile::domicile(int a = 0, string l = "NULL_CITY", int nr = 0, int rn = 0, string dt = "NULL_TYPE"):building(a,l),number_of_rezidents(nr),rooms_number(rn),domicile_type(dt){}

domicile::domicile(const domicile& d):building(d)   ///copiere informatii pentru baza
{
    number_of_rezidents = d.number_of_rezidents;
    rooms_number = d.rooms_number;
    domicile_type = d.domicile_type;
}

domicile::~domicile(){}

domicile domicile:: operator = (domicile& d)
{   (*this).building::operator=(d); ///copiere informatii pentru baza
    number_of_rezidents = d.number_of_rezidents;
    rooms_number = d.rooms_number;
    domicile_type=d.domicile_type;
    return (*this);
}

double domicile::payment_per_rezident()
{
    return 1.0*this->get_price_per_sqm()*this->get_area()/number_of_rezidents;
}

istream& operator >> (istream& in, domicile& d)
{
    ///citim datele obiectului, construim un obiect auxiliar cu acestea si transferam informatiile auxiliarului obiectului pentru care se face citirea
    int area,nr_rez,room_nr;
    string city,dom_type;
    in>>area>>city>>nr_rez>>room_nr>>dom_type;
    domicile aux(area,city,nr_rez,room_nr,dom_type);
    d = aux;
    return in;
}

ostream& operator << (ostream& out, domicile& d)
{
    d.display();
    out<<"\n";
    return out;
}

bool operator == (domicile d1, domicile d2)
{
    return (building(d1)==building(d2))*(d1.number_of_rezidents==d2.number_of_rezidents)*(d1.rooms_number==d2.rooms_number)*(d1.domicile_type==d2.domicile_type);
}

void domicile::display()
{
    building::display();
    cout<<" and serves as a "<<domicile_type<<" domicile with "<<rooms_number<<" rooms and shelters "<<number_of_rezidents<<" people";
}

void domicile::type()
{
    cout<<"domicile\n";
}

class headquarters: public virtual building{
public:
    headquarters(int,string,int,int);
    headquarters(const headquarters&);
    virtual~headquarters();
    headquarters operator = (headquarters&);
    friend istream& operator >> (istream&, headquarters&);
    friend ostream& operator << (ostream&, headquarters&);
    friend bool operator == (headquarters, headquarters);
    double monthly_profit();
    void display();
    void own_display();
    void type();
private:
    int employees_number,monthly_income;
};

headquarters::headquarters(int a = 0, string l = "NULL_CITY", int en = 0, int mi = 0):building(a,l),employees_number(en),monthly_income(mi){}

headquarters::headquarters(const headquarters& h):building(h)
{
    employees_number = h.employees_number;
    monthly_income = h.monthly_income;
}

headquarters::~headquarters(){}

headquarters headquarters:: operator = (headquarters& h)
{
    (*this).building::operator=(h);
    employees_number = h.employees_number;
    monthly_income = h.monthly_income;
    return (*this);
}

void headquarters::display()
{
    building::display();
    cout<<" and serves as a headquarters where "<<employees_number<<" employees work and generate "<<monthly_income<<"$ per month";}

void headquarters::own_display(){cout<<" and serves as a headquarters where "<<employees_number<<" employees work and generate "<<monthly_income<<"$ per month";}

double headquarters::monthly_profit()
{
    return 1.0*monthly_income-1.0*this->get_price_per_sqm()*this->get_area();
}

istream& operator >> (istream& in, headquarters& h)
{
    ///citim datele obiectului, construim un obiect auxiliar cu acestea si transferam informatiile auxiliarului obiectului pentru care se face citirea
    int area,emp_nr,month_income;
    string city;
    in>>area>>city>>emp_nr>>month_income;
    headquarters aux(area,city,emp_nr,month_income);
    h = aux;
    return in;
}

ostream& operator << (ostream& out, headquarters& h)
{
    h.display();
    out<<"\n";
    return out;
}

bool operator == (headquarters h1, headquarters h2)
{
    return (building(h1)==building(h2))*(h1.monthly_income==h2.monthly_income)*(h1.employees_number==h2.employees_number);
}

void headquarters::type()
{
    cout<<"headquarters\n";
}

class domicile_headquarters: public domicile,headquarters{
public:
    domicile_headquarters(int,string,int,int,string,int,int);
    domicile_headquarters(const domicile_headquarters&);
    virtual~domicile_headquarters();
    domicile_headquarters operator = (domicile_headquarters&);
    friend istream& operator >> (istream&, domicile_headquarters&);
    friend ostream& operator << (ostream&, domicile_headquarters&);
    friend bool operator == (domicile_headquarters,domicile_headquarters);
    void display();
    void type();
};

domicile_headquarters::domicile_headquarters(int a = 0, string l = "NULL_CITY", int nr = 0, int rn = 0, string dt = "NULL_TYPE", int en = 0, int mi = 0):building(a,l),domicile(a,l,nr,rn,dt),headquarters(a,l,en,mi){}

domicile_headquarters::domicile_headquarters(const domicile_headquarters& dh):building(dh),domicile(dh),headquarters(dh){}

domicile_headquarters::~domicile_headquarters(){}

domicile_headquarters domicile_headquarters:: operator = (domicile_headquarters& dh)
{
    (*this).building::operator=(dh);
    (*this).domicile::operator=(dh);
    (*this).headquarters::operator=(dh);
    return (*this);
}

void domicile_headquarters::display()
{
    domicile::display();
    headquarters::own_display();
}

void domicile_headquarters::type()
{
    cout<<"domicile_headquarters\n";
}

istream& operator >> (istream& in, domicile_headquarters& dh)
{
    ///citim datele obiectului, construim un obiect auxiliar cu acestea si transferam informatiile auxiliarului obiectului pentru care se face citirea
    int area,emp_nr,month_income,nr_rez,room_nr;
    string city,dom_type;
    in>>area>>city>>nr_rez>>room_nr>>dom_type>>emp_nr>>month_income;
    domicile_headquarters aux(area,city,nr_rez,room_nr,dom_type,emp_nr,month_income);
    dh = aux;
    return in;
}

ostream& operator << (ostream& out, domicile_headquarters& dh)
{
    dh.display();
    out<<"\n";
    return out;
}

bool operator == (domicile_headquarters dh1, domicile_headquarters dh2)
{
    return (domicile(dh1)==domicile(dh2))*(headquarters(dh1)==headquarters(dh2));
}


int kb,kd,kh,kdh;

building vb[1000];
domicile vd[1000];
headquarters vh[1000];
domicile_headquarters vdh[1000];

void read(int nr)
{
    int ch;

    for (int i = 1; i <= nr; i++)
    {
        cout<<"What kind of object do you want to read?\n1 building\n2 domicile\n3 headquarters\n4 domicile_headquarters\n";
        cin>>ch;
        switch (ch)
        {
            case 1:
                cout<<"Enter the surface and location, in this order!\n";
                cin>>vb[kb++];
                break;
            case 2:
                cout<<"Enter the surface,location,number of rezidents,number of rooms and domicile type in this order!\n";
                cin>>vd[kd++];
                break;
            case 3:
                cout<<"Enter the surface,location,number of employees and monthly income in this order!\n";
                cin>>vh[kh++];
                break;
            case 4:
                cout<<"Enter the surface,location,number of rezidents,number of rooms,domicile type,number of employees and monthly income in this order!\n";
                cin>>vdh[kdh++];
                break;
            default:
                cout<<"Invalid choice!\n";
                break;
        }
    }
}

void display(int type)
{
    switch (type)
    {
        case 1:
            for (int i = 0; i < kb; i++)    cout<<vb[i];
            break;
        case 2:
            for (int i = 0; i < kd; i++)    cout<<vd[i];
            break;
        case 3:
            for (int i = 0; i < kh; i++)    cout<<vh[i];
            break;
        case 4:
            for (int i = 0; i < kdh; i++)   cout<<vdh[i];
            break;
        default:
            cout<<"Invalid choice!\n";
            break;
    }
}

void modify(int type)
{
    cout<<"Enter the data of the object(surface,location";

    switch (type)
    {
        case 1:
            {
                cout<<"):\n";
                building find_object,aux;
                cin>>find_object;
                cout<<"Now enter the new data:\n";
                cin>>aux;
                for (int i = 0; i < kb; i++)
                    if (vb[i]==find_object)
                        vb[i]=aux;
            }
            break;

        case 2:
            {
                cout<<",number of rezidents,number of rooms,domicile type):\n";
                domicile find_object,aux;
                cin>>find_object;
                cout<<"Now enter the new data:\n";
                cin>>aux;
                for (int i = 0; i < kd; i++)
                    if (vd[i]==find_object)
                        vd[i]=aux;
            }
            break;

        case 3:
            {
                cout<<",number of employees,monthly income):\n";
                headquarters find_object,aux;
                cin>>find_object;
                cout<<"Now enter the new data:\n";
                cin>>aux;
                for (int i = 0; i < kh; i++)
                    if (vh[i]==find_object)
                        vh[i]=aux;
            }
            break;

        case 4:
            {
                cout<<",number of rezidents,number of rooms,domicile type,number of employees,monthly income):\n";
                domicile_headquarters find_object,aux;
                cin>>find_object;
                cout<<"Now enter the new data:\n";
                cin>>aux;
                for (int i = 0; i < kdh; i++)
                    if (vdh[i]==find_object)
                        vdh[i]=aux;
            }
            break;

    }
}

int main()
{
    char x;

    ///constructori parametrizati,operatori,variabile si functii statice clasa building

    building b1,b2(100),b3(150,"Constanta"),b4(b2),b5;

    cout<<b1<<b2<<b3<<b4;

    b1 = b3;

    cout<<b1;

    cout<<b5;

    building::set_price_per_sqm(0.5);

    cout<<building::get_price_per_sqm();

    cout<<"\n";

    ///constructori parametrizati, operatori, metode clasa domicile

    domicile a1(150,"Constanta"),a2(180,"Mangalia",5),a3(200,"Cluj",4,6),a4(110,"Arad",5,6,"duplex"),a5(a3);

    cout<<a1<<a2<<a3<<a4<<a5;

    a5 = a2;

    cout<<a5;

    cout<<a5;

    cout<<a4.payment_per_rezident();

    cout<<"\n";

    ///constructori parametrizati, operatori, metode clasa headquarters

    headquarters h1(170,"Sibiu"),h2(100,"Tulcea",20),h3(200,"Iasi",30,1500),h4(h2);

    cout<<h1<<h2<<h3<<h4;

    h4 = h2;

    cout<<h4;

    cout<<h4;

    cout<<h3.monthly_profit();

    cout<<"\n";

    ///constructori parametrizati, operatori, metode clasa headquarters

    domicile_headquarters dh1(150,"Constanta"),dh2(150,"Constanta",4,3,"apartment"),dh3(150,"Constanta",4,3,"apartment",2,1000),dh4(dh3);

    cout<<dh1<<dh2<<dh3<<dh4;

    dh2 = dh4;

    cout<<dh2;

    cout<<dh3;

    ///upcasting

    building* ptr_b = new domicile(150,"Otopeni",4,5,"apartment");

    ptr_b->type();

    domicile *ptr_d = new domicile_headquarters(150,"Constanta",4,3,"apartment",2,1000);

    ptr_d->type();

    cout<<ptr_d->payment_per_rezident()<<"\n";

    ///downcasting si try & catch

    try
    {
        domicile* ptr_h = dynamic_cast<domicile*>(ptr_b);
        ptr_h->type();
        ptr_h->display();
    }
    catch(runtime_error const e)
    {
        cout<<"Error!";
    }

    cout<<"\n";

    try
    {
        domicile_headquarters* ptr_dh = dynamic_cast<domicile_headquarters*>(ptr_d);
        ptr_dh->type();
        ptr_dh->display();
    }
    catch(runtime_error const e)
    {
        cout<<"Error!";
    }

    ///meniul interactiv

    cout<<"\nEnter any letter to clear the console: ";

    cin>>x;

    system("cls");

    ///inceputul meniului interactiv unde se realizeaza citirea a n obiecte, aici se exemplifica si citirea

    int control = 1;

    int choice;

    while(control)
    {
        cout<<"Welcome! Choose one of the following options by entering the corresponding digit:\n1 Reading real estate data\n2 Displaying real estate data\n3 Modification of the data of a real estate\nAny other key to exit\n";

        cin>>choice;

        switch (choice)
        {
            case 1:
                int nr;
                cout<<"How many objects do you want to read?(enter a natural number and it has to be smaller than 4000)\n";
                cin>>nr;
                if (nr<1 || nr>4000)  break;
                read(nr);
                break;

            case 2:
                int type;
                cout<<"What kind of estates would you like to display?\n1 building\n2 domicile\n3 headquarters\n4 domicile_headquarters\n";
                cin>>type;
                display(type);
                break;

            case 3:
                int m_type;
                cout<<"What kind of object would you like to modify?\n1 building\n2 domicile\n3 headquarters\n4 domicile_headquarters\n";
                cin>>m_type;
                modify(m_type);
                break;

            default:
                control = 0;
                break;
        }
    }

    return 0;
}
