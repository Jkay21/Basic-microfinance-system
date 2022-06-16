#include<iostream>
#include<fstream>
#include<cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
class account_query
{
private:
    char account_number[20];
    char firstName[10];
    char lastName[10];
    float total_Balance;
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};
void account_query::read_data()
{
    cout<<"\nEntrer le Numero de compte: ";
    cin>>account_number;
    cout<<"Entrer le nom de famille: ";
    cin>>firstName;
    cout<<"Entrer le Prenom: ";
    cin>>lastName;
    cout<<"Entrer le solde: ";
    cin>>total_Balance;
    cout<<endl;
}
void account_query::show_data()
{
    cout<<"Numero de compte: "<<account_number<<endl;
    cout<<"Nom: "<<firstName<<endl;
    cout<<"Prenom: "<<lastName<<endl;
    cout<<"Solde: \nFbu:  "<<total_Balance<<endl;
    cout<<"-------------------------------"<<endl;
}
void account_query::write_rec()
{
    ofstream outfile;
    outfile.open("record.bank", ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}
void account_query::read_rec()
{
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"Erreur fichier non trouver!!"<<endl;
        return;
    }
    cout<<"\n****Base de données****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            show_data();
        }
    }
    infile.close();
}
void account_query::search_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"Erreur fichier non trouver!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n Il y'a "<<count<<" fichier dans la base de données";
    cout<<"\n Enter numero du compte pour la recherche: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_data();
}
void account_query::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("record.bank", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nErreur fichier non trouver!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n Il y'a "<<count<<" fichier dans la base de données";
    cout<<"\n Entrer le numero du compte: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Le compte "<<n<<"a comme données"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.bank", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void account_query::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nErreur fichier non trouver!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n Il y'a "<<count<<" fichier dans la base de données";
    cout<<"\n Entrer le numero de compte: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank", ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0; i<count; i++)
    {
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
}
int main()
{
    account_query A;
    int choice;
    cout<<":::::::::::::::::::::UMUCO MICROFINANCE System::::::::::::::::::::"<<endl;
    while(true)
    {
        cout<<"\nOptions: ";
        cout<<"\n\t1-->Enregistrement du client";
        cout<<"\n\t2-->Informations des clients";
        cout<<"\n\t3-->Recherche";
        cout<<"\n\t4-->Modifier les informations";
        cout<<"\n\t5-->Supprimer";
        cout<<"\n\t6-->Quitter";
        cout<<"\nEntrer votre choix(1-6): ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEntrer un choix correcte";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
