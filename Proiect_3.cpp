#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <stdio.h>
using namespace std;
class Trainer
{
protected:
    string nume;
    int salariu;
    string LimbajeProg;
public:
    Trainer();
    Trainer(string,int,string);
    Trainer(const Trainer& t);
    Trainer& operator=(const Trainer& t);
    string getNume(){return this->nume;}
    int getSalariu(){return this->salariu;}
    string getLimbajeProg(){return this->LimbajeProg;}
    void setNume(string nume){this->nume=nume;}

friend istream& operator >>(istream& in,Trainer &t);
friend ostream& operator <<(ostream& out,const Trainer &t);
~Trainer(){}
};
Trainer::Trainer()
{
    this->nume="Anonim";
    this->salariu=0;
    this->LimbajeProg="C++";
}
Trainer::Trainer(string nume,int salariu,string LimbajeProg)
{
    this->nume=nume;
    this->salariu=salariu;
    this->LimbajeProg=LimbajeProg;
}
Trainer::Trainer(const Trainer& t)
{
    this->nume=t.nume;
    this->salariu=t.salariu;
    this->LimbajeProg=t.LimbajeProg;
}
Trainer&Trainer:: operator =(const Trainer& t)
{
    this->nume=t.nume;
    this->salariu=t.salariu;
    this->LimbajeProg=t.LimbajeProg;
}
istream& operator >>(istream& in,Trainer& t)
{
    cout<<"Dati numele trainerului:";
    in>>t.nume;
    cout<<endl;

    cout<<"Limbajele de programare stiute de trainer sunt:";
    in>>t.LimbajeProg;
    cout<<endl;

    cout<<"Salariul trainerului:";
    in>>t.salariu;
    cout<<endl;

    return in;
}
ostream& operator <<(ostream& out,const Trainer& t)
{
    cout<<"Numele trainer-ului este:"<<t.nume<<endl;
    cout<<"Trainer-ul cunoaste limbajele:"<<t.LimbajeProg<<endl;
    cout<<"Salariul trainer-ului este:"<<t.salariu<<endl;

    return out;
}
class IOInterface
{
public:
    virtual ostream& afisare(ostream&)const=0;
    virtual istream& citire(istream&)=0;
};
class Curs:public IOInterface
{
protected:
    string denumire;
    string limbaj;
    int dificultate;
    float pret;
    Trainer* trainer;
public:
    Curs();
    Curs(string denumire,string limbaj,int dificultate,float pret,Trainer* trainer);
    Curs(const Curs& c);
    Curs& operator = (const Curs& c);
string getDenumire(){return this->denumire;}
void setDenumire(string denumire){this->denumire=denumire;}
float getPret(){return this->pret;}
void setTrainer(Trainer* trainer){this->trainer=trainer;}
Trainer* getTrainer(){return this->trainer;}

istream& citire(istream& in){
    cout<<"Dati numele cursului:";
    in>>this->denumire;
    cout<<endl;

    cout<<"Numele limbajului de programare este:";
    in>>this->limbaj;
    cout<<endl;

    cout<<"Nivelul de dificultate este:";
    in>>this->dificultate;
    cout<<endl;

    cout<<"Pretul cursului este:";
    in>>this->pret;
    cout<<endl;

    return in;
}
ostream& afisare(ostream& out)const
{
    out<<"Numele cursului este:"<<this->denumire<<endl;
    out<<"Limbajul predat la acest curs este:"<<this->limbaj<<endl;
    out<<"Nivelul de dificultate al cursului este:"<<this->dificultate<<endl;
    out<<"Pretul cursului este:"<<this->pret<<endl;
    if(this->trainer!=NULL)
         out<<"Trainer-ul: "<<this->trainer->getNume()<<endl;
    else out<<"Trainer :Anonim"<<endl;
    return out;
}
friend istream& operator >>(istream& in,Curs& c);
friend ostream& operator <<(ostream& out,const Curs& c);
virtual float Calculeaza() const
 {
     return this->pret;
 }

 virtual ~Curs()
 {
     this->trainer=NULL;
 }
};
Curs::Curs()
{
    this->denumire="Anonym";
    this->limbaj="C++";
    this->dificultate=0;
    this->pret=0;
    this->trainer=NULL;
}
Curs::Curs(string denumire,string limbaj,int dificultate,float pret,
           Trainer* trainer):denumire(denumire),limbaj(limbaj),
           dificultate(dificultate),pret(pret),trainer(trainer){}
Curs::Curs(const Curs& c)
{
    this->denumire=c.denumire;
    this->limbaj=c.limbaj;
    this->dificultate=c.dificultate;
    this->pret=c.pret;
    this->trainer=c.trainer;
}
Curs& Curs ::operator=(const Curs &c)
{
    if(this!=&c)
    {this->denumire=c.denumire;
    this->limbaj=c.limbaj;
    this->dificultate=c.dificultate;
    this->pret=c.pret;
    this->trainer=c.trainer;
    }
    return *this;

}
istream& operator >> (istream & in,Curs &c)
{
    return c.citire(in);
}
ostream& operator << (ostream& out,const Curs &c)
{
    return c.afisare(out);
}

class CursFizic:virtual public Curs
{
protected:
    string locatie;
    int eleviFizic;
public:
    CursFizic();
    CursFizic(string denumire,string limbaj,int dificultate,float pret,
               Trainer* trainer,string locatia,int eleviFizic);
    CursFizic(const CursFizic& c);
    CursFizic& operator=(const CursFizic& c);
int getEleviFizic(){return this->eleviFizic;}

istream& citire(istream& in) override
{
    Curs::citire(in);

    cout<<"Dati locatia:";
    in>>this->locatie;
    cout<<endl;

    cout<<"Numarul de elevi prezenti fizic:";
    in>>this->eleviFizic;
    cout<<endl;

    return in;
}
ostream& afisare(ostream& out)const override
{
    Curs::afisare(out);

    cout<<"Locatia cursului este:"<<this->locatie<<endl;
    cout<<"Numarul de elevi prezenti este:"<<this->eleviFizic<<endl;

    return out;
}
float Calculeaza() const
{
    return this->pret*3;
}

virtual ~CursFizic(){}
};
CursFizic::CursFizic():Curs(){
    this->locatie="Militari";
    this->eleviFizic=0;
}
CursFizic::CursFizic(string denumire, string limbaj, int dificultate,float pret,
                     Trainer* trainer,string locatie,int eleviFizic):
                    Curs(denumire,limbaj,dificultate,pret,trainer)
{
    this->locatie=locatie;
    this->eleviFizic=eleviFizic;
}
CursFizic::CursFizic(const CursFizic& c):Curs(c)
{
    this->locatie=c.locatie;
    this->eleviFizic=c.eleviFizic;
}
CursFizic&CursFizic:: operator =(const CursFizic& c)
{
        if(this!=&c)
        {
            Curs::operator =(c);
            this->locatie=c.locatie;
            this->eleviFizic=c.eleviFizic;
        }
        return *this;
}

class CursOnline:virtual public Curs
{
protected:
    string platforma;
    int eleviOnline;
public:
    CursOnline();
    CursOnline(string denumire,string limbaj,int dificultate,float pret,
               Trainer* trainer,string platforma, int eleviOnline);
    CursOnline(const CursOnline& c);
    CursOnline& operator =(const CursOnline& c);
istream& citire(istream& in) override
{
    Curs::citire(in);
    cout<<"Dati numele platformei:";
    in>>this->platforma;
    cout<<endl;

    cout<<"Cati elevi sunt online:";
    in>>this->eleviOnline;
    cout<<endl;

    return in;
}
ostream& afisare(ostream& out)const override
{
    Curs::afisare(out);
    cout<<"Platforma pe care se vor conecta copiii este:"<<this->platforma<<endl;
    cout<<"Numarul de copii online este:"<<this->eleviOnline<<endl;
    return out;
}
float Calculeaza() const
{
    return this->pret*2;
}
int getEleviOnline(){return this->eleviOnline;}
virtual ~CursOnline(){}
};
CursOnline::CursOnline():Curs()
{
    this->platforma="Meet";
    this->eleviOnline=0;
}
CursOnline::CursOnline(string denumire,string limbaj,int dificultate,float pret,Trainer* trainer,string platforma, int eleviOnline):Curs(denumire,limbaj,dificultate,pret,trainer)
{
    this->platforma=platforma;
    this->eleviOnline=eleviOnline;
}
CursOnline::CursOnline(const CursOnline& c):Curs(c)
{
    this->platforma=c.platforma;
    this->eleviOnline=eleviOnline;
}
CursOnline&CursOnline::operator =(const CursOnline& c)
{
    if(this!=&c)
    {
        Curs:: operator=(c);
        this->platforma=c.platforma;
        this->eleviOnline=c.eleviOnline;
    }
    return *this;
}

class Hibrid:public CursFizic, public CursOnline
{
protected:
    string echipament;
public:
    Hibrid();
    Hibrid(string denumire,string limbaj,int dificultate,float pret,
               Trainer* trainer,string locatia,int eleviFizic,
               string platforma, int eleviOnline,string echipament);
    Hibrid(const Hibrid& c);
    Hibrid& operator=(const Hibrid& c);
istream& citire(istream& in) override
{
    CursFizic::citire(in);

    cout<<"Dati numele platformei:";
    in>>this->platforma;
    cout<<endl;

    cout<<"Cati elevi sunt online:";
    in>>this->eleviOnline;
    cout<<endl;

    cout<<"De ce echipament aveti nevoie:";
    in>>this->echipament;
    cout<<endl;
    return in;
}
ostream& afisare(ostream& out) const override
{
    Curs::afisare(out);
    cout<<"Locatia cursului este:"<<this->locatie<<endl;
    cout<<"Numarul de elevi prezenti este:"<<this->eleviFizic<<endl;
    cout<<"Numarul de copii online este:"<<this->eleviOnline<<endl;
    cout<<"Platforma pe care se vor conecta copiii este:"<<this->platforma<<endl;
    cout<<"Echipamentul din sala este:"<<this->echipament<<endl;
    return out;
}
float Calculeaza() const
{
    return (this->pret*3+this->pret*2)/2;

}
virtual ~Hibrid(){}
};
Hibrid::Hibrid():Curs(),CursFizic(),CursOnline()
{
    this->echipament="videoproiector";
}
Hibrid::Hibrid(string denumire,string limbaj,int dificultate,float pret,
               Trainer* trainer,string locatia,int eleviFizic,
               string platforma, int eleviOnline,string echipament):
            Curs(denumire,limbaj,dificultate,pret,trainer),
            CursFizic(denumire,limbaj,dificultate,pret,trainer,locatie,eleviFizic)
            ,CursOnline(denumire,limbaj,dificultate,pret,trainer,platforma,eleviOnline)
{
    this->echipament=echipament;
}
Hibrid::Hibrid(const Hibrid& c):Curs(c),CursFizic(c),CursOnline(c)
{
    this->echipament=c.echipament;
}
Hibrid&Hibrid::operator =(const Hibrid& c)
{
    if(this!=&c)
    {
        CursFizic::operator=(c);
        CursOnline::operator=(c);
        this->echipament=c.echipament;
    }
    return *this;
}

class Elevi
{
protected:
    string nume;
    string curs_dorit;
    float buget;
    Curs* curs;
public:
    Elevi();
    Elevi(string,string,float,Curs*);
    Elevi(const Elevi& e);
    Elevi& operator =(const Elevi& e);
string getNume(){return this->nume;}
void setNume(string nume){this->nume=nume;}
void setCurs(Curs* curs){this->curs=curs;}
string getcurs_dorit(){return this->curs_dorit;}
float getBuget(){return this->buget;}
void setBuget(float buget){this->buget=buget;}
friend istream& operator >>(istream& in,Elevi& e);
friend ostream& operator <<(ostream& out,const Elevi& e);
float Calc_Buget()
{
    return this->buget-(this->curs->Calculeaza()*4);
}
virtual ~Elevi()
{
    this->curs=NULL;
}
};
Elevi::Elevi()
{
    this->nume="Anonim";
    this->curs_dorit="A3-DD";
    this->buget=0;
    this->curs=NULL;
}
Elevi::Elevi(string nume,string curs_dorit, float buget,Curs* curs)
{
    this->nume=nume;
    this->curs_dorit=curs_dorit;
    this->buget=buget;
    this->curs=curs;
}
Elevi::Elevi(const Elevi& e)
{
    this->nume=e.nume;
    this->curs_dorit=e.curs_dorit;
    this->buget=e.buget;
    this->curs=e.curs;
}
Elevi&Elevi::operator=(const Elevi& e)
{
    if(this!=&e)
    {this->nume=e.nume;
    this->curs_dorit=e.curs_dorit;
    this->buget=e.buget;
    this->curs=e.curs;
    }
}
istream& operator >>(istream& in,Elevi& e)
{
    cout<<"Numele elevului este:";
    in>>e.nume;
    cout<<endl;

    cout<<"Cursul pe care vrea sa-l urmeze este:";
    in>>e.curs_dorit;
    cout<<endl;

    cout<<"Dati un buget:";
    in>>e.buget;
    cout<<endl;

    return in;
}
ostream& operator <<(ostream& out, const Elevi& e)
{
    out<<"Numele elevului este:"<<e.nume<<endl;
    out<<"Bugetul sau este:"<<e.buget<<endl;
    if(e.curs!=NULL)
        out<<"Cursul :"<<e.curs->getDenumire()<<endl;
    else out<<"Cursul: Anonim:";

    return out;
}
void clean()
{
    system("CLS");
}
void Cursuri()
{
    cout<<"1.Curs fizic.\n";
    cout<<"2.Curs online.\n";
    cout<<"3.Curs hibrid.\n";
    cout<<"Alegeti tipul de curs:";
}
void displayTrainer()
{
    cout<<"\t\t\t\t-----Meniul Trainerului-----\t\t\t\t\n"<<endl<<endl;
    cout<<"1.Vedeti cursurile dvs.\n";
    cout<<"2.Salariul dvs.\n";
    cout<<"Alegeti optiunea:";
}
void displayAdmin()
{

    cout<<"\t\t\t-----Meniul Administratorului-----\t\t\t\t\n";
    cout<<"1.Adaugati un curs.\n";
    cout<<"2.Stergeti un curs.\n";
    cout<<"3.Vezi cursuri.\n";
    cout<<"4.Adaugati un trainer.\n";
    cout<<"5.Stergeti un trainer.\n";
    cout<<"6.Adaugati un elev.\n";
    cout<<"7.Stergeti un elev.\n";
    cout<<"8.Vezi toti trainerii.\n";
    cout<<"9.Vezi toti elevii.\n";
    cout<<"10.Aloca trainer-ului un curs.\n";
    cout<<"11.Inscrie elevul intr-un curs.\n";
    cout<<"12.Detalii trainer.\n";
    cout<<"13.Detalii elev.\n";
    cout<<"14.Vezi costurile unui curs.\n";
    cout<<"15.Import datele trainer-ului.\n";
    cout<<"16.Export datele trainer-ului.\n";
    cout<<"Alegeti optiunea:";
}
void MeniuPrincipal()
{
    clean();
    cout<<"\t\t\t\t---->PLAYCODE<----\t\t\t\t"<<endl<<endl;
    cout<<"1.Meniu Admin.\n";
    cout<<"2.Meniu Trainer.\n";
    cout<<"Alegeti optiunea:";
}
void pauza(int secunde)
{
    this_thread::sleep_for(chrono::seconds(secunde));
}
void Default()
{
    cout<<"Comanda incorecta! Va rugam incercati din nou.\n";
    cin.ignore();
    cin.get();
    clean();
}

vector<Trainer*>listaTraineri;
int contor=0;
void importTrainer(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr<<"A intervenit o eroare!"<<endl;
        return;
    }

    contor++;
    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string nume;
        int salariu;
        string LimbajeProg;

        getline(ss, nume, ',');
        ss >> salariu;
        ss.ignore();
        getline(ss, LimbajeProg, ',');


        Trainer* trainer = new Trainer(nume,salariu,LimbajeProg);
        listaTraineri.push_back(trainer);
    }

    contor=listaTraineri.size();
    file.close();
}
void exportTrainer(const string& Filename, Trainer* trainer_exp)
{
    ofstream file(Filename, ios::app);
    if (!file.is_open())
    {
        cerr << "A intervenit o eroare la deschiderea fisierului!" << endl;
        return;
    }
        file << trainer_exp->getNume() << ","
             << trainer_exp->getSalariu() << ","
             << trainer_exp->getLimbajeProg() << endl;


    file.close();
}

class Meniu
{
private:
    static Meniu *m;
    Meniu()=default;
    Meniu(const Meniu&)=delete;
    static int nr;
public:
    static Meniu* getNr()
    {
        nr++;
        if(!m)
            m=new Meniu();


        return m;
    }
    void Aplicatie()
    {
        listaTraineri.push_back(new Trainer("Andreea", 2000, "C++"));
        listaTraineri.push_back(new Trainer("Ion", 3000, "Java"));
        listaTraineri.push_back(new Trainer("Maria", 40000, "Python"));
        listaTraineri.push_back(new Trainer("George", 5000, "JavaScript"));
        listaTraineri.push_back(new Trainer("Elena", 2000, "C#"));
        listaTraineri.push_back(new Trainer("Alex", 6000, "Ruby"));
        listaTraineri.push_back(new Trainer("Diana", 3000, "PHP"));
        listaTraineri.push_back(new Trainer("Vlad", 4000, "Java"));
        listaTraineri.push_back(new Trainer("Roxana", 5000, "C#"));
        listaTraineri.push_back(new Trainer("Radu", 2000, "Go"));

        vector<Curs*> listaCursuri;
        listaCursuri.push_back(new CursFizic("A1-F", "C++", 1, 50, listaTraineri[0], "Militari", 9));
        listaCursuri.push_back(new CursFizic("A2-F", "Python", 2, 150, listaTraineri[2], "Piata Unirii", 5));
        listaCursuri.push_back(new CursFizic("A3-F", "PHP", 6, 100, listaTraineri[6], "Militari", 3));
        listaCursuri.push_back(new CursOnline("B1-O", "JavaScript", 4, 100, listaTraineri[3], "Meet", 6));
        listaCursuri.push_back(new CursOnline("B2-O", "Python", 3, 80, listaTraineri[2], "Zoom", 8));
        listaCursuri.push_back(new CursOnline("C1-O", "Java", 2, 120, listaTraineri[7], "Teams", 7));
        listaCursuri.push_back(new Hibrid("B3-H", "C#", 3, 175, listaTraineri[4], "Universitate", 5, "Meet", 7, "Videoproiector"));
        listaCursuri.push_back(new Hibrid("B3-H", "C#", 3, 10, listaTraineri[8], "Universitate", 8, "Zoom", 7, "tabla-interactiva"));
        listaCursuri.push_back(new Hibrid("C2-H", "Java", 2, 120, listaTraineri[1], "Taberei", 6, "Zoom", 8, "tableta_grafica"));
        listaCursuri.push_back(new Hibrid("D5-H", "Python", 4, 180, listaTraineri[2], "Militari", 7, "Teams", 6, "videoproietor"));

        vector<Elevi*>listaElevi;
        listaElevi.push_back(new Elevi("Andrei","A2-F",1500,listaCursuri[1]));
        listaElevi.push_back(new Elevi("Andrei", "A2-F", 1500,listaCursuri[1]));
        listaElevi.push_back(new Elevi("Maria", "A1-F", 1300,listaCursuri[0]));
        listaElevi.push_back(new Elevi("Ionut", "B2-O", 1800,listaCursuri[4]));
        listaElevi.push_back(new Elevi("Elena", "B3-H", 2000,listaCursuri[6]));
        listaElevi.push_back(new Elevi("Vlad", "C1-O", 1600,listaCursuri[5]));
        listaElevi.push_back(new Elevi("Diana", "A3-F", 1700,listaCursuri[2]));
        listaElevi.push_back(new Elevi("Alex", "D5-H", 1900,listaCursuri[9]));
        listaElevi.push_back(new Elevi("Roxana", "C2-H", 2100,listaCursuri[8]));
        listaElevi.push_back(new Elevi("George", "B1-O", 1400,listaCursuri[3]));
        listaElevi.push_back(new Elevi("Ana", "B3-H", 175,listaCursuri[7]));

        bool stop = false;
bool stop1=false;

while (!stop)
{int comanda;
     try
            {

                MeniuPrincipal();
                cin >> comanda;
                if (cin.fail())
                {
                    throw invalid_argument("Va rog introduceti o comanda valida.");
                }

            }
            catch (const invalid_argument& e)
            {
                cout << "Eroare: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clean();
            }
    switch (comanda)
    {
    case 1:
        {
            while(!stop1)
            {clean();

            int comanda1;

             try
            {

                displayAdmin();
                cin >> comanda1;
                if (cin.fail())
                {
                    throw invalid_argument("Input invalid. Te rog introdu o comanda valida.");
                }

            }
            catch (const invalid_argument& e)
            {
                cout << "Eroare: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clean();

            }
            switch (comanda1)
            {
            case 1:
                {clean();

                    int comanda2;
                   try
                        {

                            Cursuri();
                            cin >> comanda2;
                            if (cin.fail())
                            {
                                throw invalid_argument("Comanda invalida. Va rog introduceti o comanda valida.");
                            }

                        }
                        catch (const invalid_argument& e)
                        {
                            cout << "Eroare: " << e.what() << endl;
                            cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            clean();

                        }
                    switch (comanda2)
                        {
                        case 1:
                        {clean();
                            Curs* a = new CursFizic();
                            cin >> *a;
                            listaCursuri.push_back(a);
                            break;
                        }
                        case 2:
                        {clean();
                            Curs* a = new CursOnline();
                            cin >> *a;
                            listaCursuri.push_back(a);
                            break;
                        }
                        case 3:
                        {clean();
                            Curs* a = new Hibrid();
                            cin >> *a;
                            listaCursuri.push_back(a);
                            break;
                        }
                        default:
                            {
                                Default();
                                break;
                            }
                        }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;
                }
            case 2:
                {clean();
                    int comanda3;
                    try
                        { Cursuri();
                            cin >> comanda3;
                            if (cin.fail())
                            {
                                throw invalid_argument("Comanda invalida. Va rog introduceti o comanda valida.");
                            }

                        }
                        catch (const invalid_argument& e)
                        {
                            cout << "Eroare: " << e.what() << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    switch(comanda3)
                    {
                        case 1:
                            {clean();
                            cout << "Lista cursurilor fizice:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<CursFizic*>(listaCursuri[i]) != NULL&&
                                dynamic_cast<Hibrid*>(listaCursuri[i]) == NULL)
                                cout << i+1<<". "<<*listaCursuri[i]<< endl;

                            }
                        cout<<"Introduceti numarul cursului pe care vreti sa-l stergeti.";
                        int opt;
                        cin>>opt;
                        bool gasit=false;

                        try{
                            if(opt>0&&opt<=listaCursuri.size())
                            {
                               gasit=true;
                            for(int i=0;i<listaCursuri.size();i++)
                            {
                                opt-=1;
                                if (dynamic_cast<CursFizic*>(listaCursuri[i]) != NULL&&
                                    dynamic_cast<Hibrid*>(listaCursuri[i]) == NULL)
                                    listaCursuri.erase(listaCursuri.begin()+opt);

                            }
                            }
                            else{
                             if (gasit==false)
                            {
                                throw runtime_error("Nu exista acest curs.");
                                cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();

                            }
                            }
                        }
                        catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                        break;

                            }
                        case 2:
                            {clean();
                            cout << "Lista cursurilor online:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<CursOnline*>(listaCursuri[i]) != NULL&&
                                dynamic_cast<Hibrid*>(listaCursuri[i]) == NULL)
                                cout << i+1<<". "<<*listaCursuri[i]<< endl;

                            }
                        cout<<"Introduceti numarul cursului pe care vreti sa-l stergeti.";
                        int opt;
                        cin>>opt;
                        bool gasit=false;

                        try{
                            if(opt>0&&opt<=listaCursuri.size())
                            {
                               gasit=true;
                            for(int i=0;i<listaCursuri.size();i++)
                            {
                                opt-=1;
                                if (dynamic_cast<CursOnline*>(listaCursuri[i]) != NULL&&
                                    dynamic_cast<Hibrid*>(listaCursuri[i]) == NULL)
                                    listaCursuri.erase(listaCursuri.begin()+opt);

                            }
                            }
                            else{
                             if (gasit==false)
                            {
                                throw runtime_error("Nu exista acest curs.");

                            }
                            }
                        }
                        catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                        break;

                            }
                    case 3:
                            {clean();
                            cout << "Lista cursurilor hibrid:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<Hibrid*>(listaCursuri[i]) != NULL)
                                cout << i+1<<". "<<*listaCursuri[i]<< endl;

                            }
                        cout<<"Introduceti numarul cursului pe care vreti sa-l stergeti.";
                        int opt;
                        cin>>opt;
                        bool gasit=false;

                        try{
                            if(opt>0&&opt<=listaCursuri.size())
                            {
                               gasit=true;
                            for(int i=0;i<listaCursuri.size();i++)
                            {
                                opt-=1;
                                if (dynamic_cast<Hibrid*>(listaCursuri[i]) != NULL)
                                    listaCursuri.erase(listaCursuri.begin()+opt);

                            }
                            }
                            else{
                             if (gasit==false)
                            {
                                throw runtime_error("Nu exista acest curs.");

                            }
                            }
                        }
                        catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                        break;

                            }
                    default:
                        {
                            Default();
                            break;
                        }
                    break;
                    }

                }
            case 3:
                {clean();
                    int comanda4;
                    try
                        {

                            Cursuri();
                            cin >> comanda4;
                            if (cin.fail())
                            {
                                throw invalid_argument("Input invalid. Te rog introdu o comanda valida.");
                            }

                        }
                        catch (const invalid_argument& e)
                        {
                            cout << "Eroare: " << e.what() << endl;
                            clean();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        }
                    switch(comanda4)
                    {case 1:
                        {clean();
                        if(listaCursuri.size()==0)
                            {cout<<"Nu exista cursuri fizice";
                            cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();}
                        else{
                        cout << "Lista cursurilor fizice:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<CursFizic*>(listaCursuri[i]) != NULL&&
                                dynamic_cast<Hibrid*>(listaCursuri[i]) == NULL)
                                cout << *listaCursuri[i] << endl;

                            }
                            cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                        }

                                break;
                        }
                    case 2:
                        {clean();
                        if(listaCursuri.size()==0)
                            {cout<<"Nu exista cursuri online.";
                            cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();}
                        else{
                        cout << "Lista cursurilor online:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<CursOnline*>(listaCursuri[i]) != NULL&&
                                dynamic_cast<Hibrid*>(listaCursuri[i]) == NULL)
                                cout << *listaCursuri[i] << endl;

                            }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                        }
                    break;
                        }
                    case 3:
                        {clean();
                        if(listaCursuri.size()==0)
                            {cout<<"Nu exista cursuri fizice";
                            cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();}
                        else{
                        cout << "Lista cursurilor hibrid:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<Hibrid*>(listaCursuri[i])!=NULL)
                                cout << *listaCursuri[i] << endl;

                            }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                        }
                    break;
                        }
                    default:
                        {
                            Default();
                            clean();
                        }
                    }

                break;
                }
            case 4:
                {clean();
                    Trainer a;
                    cin>>a;
                    listaTraineri.push_back(&a);
                    cout<<endl;
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;
                }
            case 5:
                {
                    clean();
                    int opt;
                    cout<<"Lista de trainer:"<<endl;
                    for(int i=0;i<listaTraineri.size();i++)
                        cout<<i+1<<". "<<*listaTraineri[i]<<endl;
                    cout<<"Scrieti numarul trainer-ului pe care vreti sa-l stergeti.";
                    cin>>opt;
                    bool gasit=false;
                    try{
                    if(opt>0&& opt<=listaTraineri.size())
                    { gasit=true;
                        for(int i=0;i<listaTraineri.size();i++)
                   {
                       opt--;
                       listaTraineri.erase(listaTraineri.begin()+opt);
                       break;
                   }
                   cout<<"Trainer-ul a fost eliminat cu succes!"<<endl;
                   cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    }

                    else{
                            if (gasit==false)
                            {
                                throw out_of_range("Nu exista acest trainer.");

                            }

                    }
                    }
                    catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    break;
                }
            case 6:
                {clean();
                    Elevi a;
                    cin>>a;
                    listaElevi.push_back(&a);
                    cout<<endl;
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;
                }
            case 7:
                {
                    clean();
                    int opt;
                    cout<<"Lista de elevi:"<<endl;
                    for(int i=0;i<listaElevi.size();i++)
                        cout<<i+1<<". "<<*listaElevi[i]<<endl;
                    cout<<"Scrieti numarul elevului pe care vreti sa-l stergeti.";
                    cin>>opt;
                    bool gasit=false;
                    try{
                    if(opt>0&& opt<=listaElevi.size())
                    { gasit=true;
                        for(int i=0;i<listaElevi.size();i++)
                   {
                       opt--;
                       listaElevi.erase(listaElevi.begin()+opt);
                       break;
                   }
                   cout<<"Elevul a fost eliminat cu succes!"<<endl;
                   cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    }

                    else{
                            if (gasit==false)
                            {
                                throw out_of_range("Nu exista acest elev.");

                            }

                    }
                    }
                    catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    break;
                }
            case 8:
                {clean();
                if(listaTraineri.size()==0)
                {
                    cout<<"Nu exista traineri angajati.";
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                }
                else{
                    for(int i=0;i<listaTraineri.size();i++)
                        cout<<i+1<<". "<<*listaTraineri[i]<<endl;
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                }
                    break;
                }
            case 9:
                {clean();
                if(listaElevi.size()==0)
                {
                    cout<<"Nu exista elevi inscrisi.";
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                }
                else{
                    for(int i=0;i<listaElevi.size();i++)
                        cout<<i+1<<". "<<*listaTraineri[i]<<endl;
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                }
                    break;
                }
            case 10:
                {
                    clean();
                    int opt1,opt2;
                    bool gasit1=false;
                    bool gasit2=false;
                    cout<<"Alegeti numarul trainer-ului pentru curs:";


                    for(int i=0;i<listaTraineri.size();i++)
                        cout<<i+1<<". "<<*listaTraineri[i]<<endl;
                    cin>>opt1;
                    opt1--;

                    try{
                    if(opt1>0&& opt1<=listaTraineri.size())
                    { gasit1=true;

                    }
                     else{
                            if (gasit1==false)
                            {
                                throw out_of_range("Nu exista acest trainer.");

                            }
                     }
                    }
                     catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    cout<<"Alegeti numarul cursului:"<<endl;


                    for(int i=0;i<listaCursuri.size();i++)
                        cout<<i+1<<". "<<*listaCursuri[i]<<endl;
                    cin>>opt2;
                    opt2--;
                    try{
                    if(opt2>0&& opt2<=listaCursuri.size())
                    { gasit2=true;

                    }
                     else{
                            if (gasit2==false)
                            {
                                throw out_of_range("Nu exista acest curs.");

                            }
                     }
                    }
                     catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    listaCursuri[opt2]->setTrainer(listaTraineri[opt1]);
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;
                }
            case 11:
                {   clean();
                    int opt1,opt2;
                    bool gasit1=false;
                    bool gasit2=false;
                    cout<<"Alegeti numarul elevului pentru curs:";

                    for(int i=0;i<listaElevi.size();i++)
                        cout<<i+1<<". "<<*listaElevi[i]<<endl;
                     cin>>opt1;
                     opt1--;
                     try{
                    if(opt1>0&& opt1<=listaElevi.size())
                    { gasit1=true;

                    }
                     else{
                            if (gasit1==false)
                            {
                                throw out_of_range("Nu exista acest elev.");

                            }
                     }
                    }
                     catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    cout<<"Alegeti numarul cursului:"<<endl;

                    for(int j=0;j<listaCursuri.size();j++)
                        cout<<j+1<<". "<<*listaCursuri[j]<<endl;

                    cin>>opt2;
                    opt2--;
                    try{
                    if(opt2>0&& opt2<=listaCursuri.size())
                    { gasit2=true;

                    }
                     else{
                            if (gasit2==false)
                            {
                                throw out_of_range("Nu exista acest curs.");

                            }
                     }
                    }
                     catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    if(listaElevi[opt1]->getBuget()<listaCursuri[opt2]->getPret())
                        cout<<"Bugetul elevului nu este suficient."<<endl;
                    else
                    {cout<<"Elevul a fost alocat cu succes."<<endl;
                    listaElevi[opt1]->setCurs(listaCursuri[opt2]);}
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;

                }
            case 12:
                {clean();
                cout<<"Alege numarul trainer-ului:"<<endl;
                for(int i=0;i<listaTraineri.size();i++)
                        cout<<i+1<<". "<<listaTraineri[i]->getNume()<<endl;
                int opt;
                bool gasit=false;
                cin>>opt;
                 try{
                    if(opt>0&& opt<=listaTraineri.size())
                    { gasit=true;

                    }
                     else{
                            if (gasit==false)
                            {
                                throw out_of_range("Nu exista acest trainer.");

                            }
                     }
                    }
                    catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    for(int i=0;i<listaCursuri.size();i++)
                    {for(int j=0;j<listaTraineri.size();j++)
                        {if(listaCursuri[i]->getTrainer()->getNume()==listaTraineri[opt-1]->getNume())
                            cout<<"Trainer-ul "<<listaTraineri[opt-1]->getNume()<<" preda cursurile:"<<listaCursuri[i]->getDenumire()<<endl;
                            break;
                        }

                    }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;

                }
            case 13:
                {
                    clean();
                    cout<<"Alege numarul elevului:"<<endl;
                for(int i=0;i<listaElevi.size();i++)
                        cout<<i+1<<". "<<*listaElevi[i]<<endl;
                int opt;
                cin>>opt;
                bool gasit=false;
                try{
                if(opt>0&& opt<=listaElevi.size())
                    { gasit=true;

                    }
                     else{
                            if (gasit==false)
                            {
                                throw out_of_range("Nu exista acest elev.");

                            }
                     }
                    }
                     catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                    for(int i=0;i<listaCursuri.size();i++)
                        {if(listaElevi[opt-1]->getcurs_dorit()==listaCursuri[i]->getDenumire())
                            cout<<"Cursul la care este inscris elevul "<<listaElevi[opt-1]->getNume()<<" este:"<<listaCursuri[i]->getDenumire()<<endl;
                            listaElevi[opt-1]->setBuget(listaElevi[opt-1]->Calc_Buget()-(listaCursuri[i]->Calculeaza()*4));
                        if(listaElevi[opt-1]->getBuget()<=0)
                            {cout<<"Bugetul elevului este insuficient."<<endl;
                   for(int k=0;k<listaElevi.size();k++)
                   {
                        opt--;
                       listaElevi.erase(listaElevi.begin()+opt);
                       break;
                   }
                   cout<<"Bugetul elevului a ramas:"<<listaElevi[opt]->Calc_Buget()-(listaCursuri[i]->Calculeaza()*4)<<" RON"<<endl;
                   cout<<"Elevul a fost eliminat cu succes!"<<endl;}
                            else
                            {
                                cout<<"Cursul elevului costa: "<<listaCursuri[i]->Calculeaza()<<"/sedinta"<<endl;
                            cout<<"Bugetul elevului a ramas:"<<listaElevi[opt-1]->Calc_Buget()-(listaCursuri[i]->Calculeaza()*4)<<" RON"<<endl;

                            }
                            break;
                        }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;
                }
            case 14:
                {clean();

                    int comanda5;

                        try
                            {

                                Cursuri();
                                cin >> comanda5;
                                if (cin.fail())
                                {
                                    throw invalid_argument("Va rog introduceti o comanda valida.");
                                }

                            }
                            catch (const invalid_argument& e)
                            {
                                cout << "Eroare: " << e.what() << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                clean();
                            }
                    switch(comanda5)
                    {case 1:
                        {clean();
                        cout << "Lista cursurilor fizice:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<CursFizic*>(listaCursuri[i]) != NULL&&
                                dynamic_cast<Hibrid*>(listaCursuri[i]) == NULL)
                                cout <<i+1<<". "<< *listaCursuri[i] << endl;

                            }
                        int opt;
                        cout<<"Alegeti numarul cursului caruia vreti sa-i vedeti costurile"<<endl;
                        cin>>opt;
                        bool gasit=false;
                        try{
                    if(opt>0&& opt<=listaCursuri.size())
                    { gasit=true;

                    }
                     else{
                            if (gasit==false)
                            {
                                throw out_of_range("Nu exista acest curs fizic.");

                            }
                     }
                    }
                     catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                        for (int i=0;i<listaCursuri.size();i++)
                            {if(listaCursuri[i]==listaCursuri[opt-1])
                            {CursFizic* cursFizic = dynamic_cast<CursFizic*>(listaCursuri[i]);
                        if (cursFizic !=NULL)
                            cout <<"Costurile totale cursului "<<cursFizic->getDenumire()<<" sunt:"<<cursFizic->Calculeaza()*cursFizic->getEleviFizic()<<" RON" << endl;
                            }
                            }

                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                                break;
                        }
                    case 2:
                        {clean();
                        cout << "Lista cursurilor online:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<CursOnline*>(listaCursuri[i]) != NULL&&
                                dynamic_cast<Hibrid*>(listaCursuri[i]) == NULL)
                                cout << i+1<<". "<<*listaCursuri[i] << endl;
                            }
                        int opt;
                        cout<<"Alegeti numarul cursului caruia vreti sa-i vedeti costurile"<<endl;
                        cin>>opt;
                        bool gasit=false;
                        try{
                    if(opt>0&& opt<=listaCursuri.size())
                    { gasit=true;

                    }
                     else{
                            if (gasit==false)
                            {
                                throw out_of_range("Nu exista acest curs online.");

                            }
                     }
                    }
                     catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                        for (int i=0;i<listaCursuri.size();i++)
                            {if(listaCursuri[i]==listaCursuri[opt-1])
                            {CursOnline* cursOnline = dynamic_cast<CursOnline*>(listaCursuri[i]);
                        if (cursOnline !=NULL)
                            cout <<"Costurile totale cursului "<<cursOnline->getDenumire()<<" sunt:"<< cursOnline->Calculeaza()*cursOnline->getEleviOnline()<<" RON" << endl;
                            }
                            }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;
                        }
                    case 3:
                        {clean();
                        cout << "Lista cursurilor hibrid:" << endl;
                        for (int i=0;i<listaCursuri.size();i++)
                            {
                            if (dynamic_cast<Hibrid*>(listaCursuri[i]) != NULL)

                                cout << i+1<<". "<<*listaCursuri[i] << endl;

                            }
                        int opt;
                        cout<<"Alegeti numarul cursului caruia vreti sa-i vedeti costurile"<<endl;
                        cin>>opt;
                        bool gasit=false;
                        try{
                    if(opt>0&& opt<=listaCursuri.size())
                    { gasit=true;

                    }
                     else{
                            if (gasit==false)
                            {
                                throw out_of_range("Nu exista acest curs hibrid.");

                            }
                     }
                    }
                     catch (const exception& e)
                        {
                            cout <<endl<< "Eroare: " << e.what() << endl<<endl;
                            pauza(3);
                            clean();
                            break;
                        }
                        for (int i=0;i<listaCursuri.size();i++)
                            {if(listaCursuri[i]==listaCursuri[opt-1])
                            {Hibrid* hibrid = dynamic_cast<Hibrid*>(listaCursuri[i]);
                        if (hibrid !=NULL)
                            cout <<"Costurile totale cursului "<<hibrid->getDenumire()<<" sunt:"<< hibrid->Calculeaza()<<" RON" << endl;
                            }
                            }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                    break;
                        }

                         default:
                                {
                                    Default();
                                    break;
                                }

                    }

                break;

                }
            case 15:
                {
                    clean();

                    cout<<"Fisierul trebuie sa aiba urmatorul format pe fiecare linie: Nume, Salariu, Limbaje de programare cunoscute"<<endl;
                    cout<<"Va rog sa respectati formatul.";
                    contor = 0;
                    string fileName;
                    cout<<"Introduceti numele fisierului: ";
                    cin.ignore();
                    getline(cin, fileName);
                    importTrainer(fileName);

                    clean();
                    if(contor != 0)
                    {
                        cout<<"Importul s-a realizat cu succes!\n";
                        cin.get();
                        pauza(3);
                    }
                    cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();
                break;
                }
            case 16:
                {
                     clean();

                            try
                            {
                                bool gasit = false;

                                for (int i = 0; i < listaTraineri.size(); i++)
                                {
                                    cout << i+1<<" "<<*listaTraineri[i] << endl;
                                    gasit = true;
                                }

                                if(gasit==false)
                                {
                                    throw runtime_error("Nu exista traineri!");
                                }
                            }
                            catch(const runtime_error& e)
                            {
                                cout<<"Eroare: "<< e.what()<<endl;
                                pauza(3);
                                clean();
                            }

                            cout << "Introduceti numarul trainer-ului pe care doriti sa-l exportati: ";
                            int opt;


                            while(true)
                            {
                                try
                                {
                                    string input;
                                    cin>>input;
                                    stringstream ss(input);

                                    ss>>opt;

                                    if(ss.fail())
                                    {
                                        throw invalid_argument("Te rog introdu un ID valid.");
                                    }
                                    break;
                                }
                                catch(const invalid_argument& e)
                                {
                                    cout<<"Eroare: "<< e.what()<<endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            }
                            bool gasit1 = false;
                            try
                            {
                                if (opt >= 0 && opt <= listaTraineri.size())
                                {



                                            Trainer* trainerExport = listaTraineri[--opt];
                                            string FisierOutput;
                                            cout << "Introduceti numele fisierului pentru export: ";
                                            cin.ignore();
                                            getline(cin, FisierOutput);
                                            exportTrainer(FisierOutput, trainerExport);
                                            gasit1 = true;
                                            clean();
                                            cout<<"Exportul s-a realizat cu succes!";
                                            cin.get();
                                            break;



                                    if (gasit1==false)
                                    {
                                        cout << "Nu exista trainer-ul cu nr-ul specificat!" << endl;
                                        cin.ignore();
                                        cin.get();
                                    }
                                }
                                else
                                {
                                    throw out_of_range("ID-ul introdus nu exista!");
                                }
                            }
                            catch (const out_of_range& e)
                            {
                                cout << e.what();
                                pauza(3);
                                clean();
                            }

                            clean();
                            break;
                }
            stop1=true;
            break;
            default:
        {
            Default();
            break;
        }
            }

            }

        }
    case 2:
        {
            clean();

        for(int i=0;i<listaTraineri.size();i++)
            cout<<i+1<<". "<<listaTraineri[i]->getNume()<<endl;
        cout<<"Cine esti:"<<endl;
        int opt;
        cin>>opt;
        for(int j=0;j<listaCursuri.size();j++)
            {for(int i=0;i<listaTraineri.size();i++)
                {if(listaCursuri[j]->getTrainer()->getNume()==listaTraineri[opt-1]->getNume())
                cout<<"Sunteti alocat cursurilor:"<<listaCursuri[j]->getDenumire()<<endl;
                break;
                }

                    }

            cout << "Apasa 'enter' pentru a reveni la meniu." << endl;
                    cin.ignore();
                    while (cin.get() != '\n');
                    clean();

            break;
        }

stop=true;
    break;
    default:
        {
            Default();
            break;
        }
    }

}


    };
~Meniu()
    {
        nr--;
        if(nr==0)
            if(m)
                delete m;

    }


};
Meniu* Meniu::m=0;
int Meniu::nr=0;

int main()
{

     try
    {
        Meniu* m = Meniu::getNr();
        m->Aplicatie();
    }
    catch(...)
    {
        cout<<endl<<"A intervenit o eroare. Va rugam reporniti aplicatia."<<endl;
    }

    return 0;

}



