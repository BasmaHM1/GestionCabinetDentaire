#include <iostream>
#include <string>
using namespace std;

//class Time
class Time {
private:
    int heure;
    int minute;

public:
    // Constructeurs
    Time() : heure(0), minute(0) {} // Par d�faut
    Time(int h, int m) : heure(h), minute(m) {
        if (h < 0 || h >= 24 || m < 0 || m >= 60) {
            cout << "Heure ou minute invalide. Initialisation � 0:0.\n";
            heure = 0;
            minute = 0;
        }
    }

    // Op�rateurs
    bool operator==(const Time& t) const {
        return (heure == t.heure && minute == t.minute);
    }

    bool operator<(const Time& t) const {
        if (heure < t.heure) return true;
        if (heure == t.heure && minute < t.minute) return true;
        return false;
    }

    Time& operator++() { // Incr�mentation (pr�fixe)
        minute++;
        if (minute == 60) {
            minute = 0;
            heure++;
            if (heure == 24) {
                heure = 0;
            }
        }
        return *this;
    }

    // Amis pour entr�e/sortie
    friend ostream& operator<<(ostream& os, const Time& t) {
        os << (t.heure < 10 ? "0" : "") << t.heure << "h:"
           << (t.minute < 10 ? "0" : "") << t.minute << "m";
        return os;
    }

    friend istream& operator>>(istream& is, Time& t) {
    do {
        cout << "Entrez l'heure (0-23): ";
        is >> t.heure;
        cout << "Entrez les minutes (0-59): ";
        is >> t.minute;

        if (t.heure < 0 || t.heure >= 24 || t.minute < 0 || t.minute >= 60) {
            cout << "Heure ou minute invalide. Veuillez entrer une heure et des minutes valides.\n";
        }
    } while (t.heure < 0 || t.heure >= 24 || t.minute < 0 || t.minute >= 60);

    return is;
}

};


// Classe Date
class Date {
private:
    int jour;
    int mois;
    int annee;

public:
    Date() : jour(1), mois(1), annee(2000) {}
    Date(int j, int m, int a) : jour(j), mois(m), annee(a) {}

    void afficherDate() const {
        cout << jour << "/" << mois << "/" << annee;
    }

    void setDate(int j, int m, int a) {
        jour = j;
        mois = m;
        annee = a;
    }
};


//employe heritage
class Employe{
	protected:
	int matr;
	string nom;
	string tel;
	   virtual float salaire()=0;
	   		virtual string type()=0;
		Employe(int m=1,string n="",string t=""):matr(m),nom(n),tel(t){;}

	// Accesseurs pour les membres prot�g�s
    int getMatricule() const { return matr; }
    string getNom() const { return nom; }
    string getTel() const { return tel; }

		friend ostream& operator<<(ostream&, Employe*);
};


	 ostream& operator<<(ostream& o, Employe* E) {
    o << endl << E->type() << endl;
    o << "Matricule : " << E->getMatricule() << endl;
    o << "Nom : " << E->getNom() << endl;
    o << "Tel : " << E->getTel() << endl;
    o << "Le salaire est : " << E->salaire() << endl;
    return o;
}



class Receptionniste : public Employe{
	float SM;
	public:
	Receptionniste(int m=1,string n="",string t="",float s=0):Employe(m,n,t),SM(s){;}
	float salaire(){return SM;
	}
		string type(){
			return "Receptionniste : ";
		}
};

class Assistante : public Employe{
	float SM,prime;
	public:
	Assistante(int m=1,string n="",string t="",float s=0,float p=0):Employe(m,n,t),SM(s),prime(p){;}
	float salaire(){return SM +prime;
	}
		string type(){
			return "Assistante : ";
		}
};

class Prothesiste : public Employe{
	float SPP; //salaire par prothese
	int NP;    //nombre de prothese
	public:
	Prothesiste(int m=1,string n="",string t="",float s=0,int nb=0):Employe(m,n,t),SPP(s),NP(nb){;}
	float salaire(){return SPP*NP;
	}
		string type(){
			return "Prothesiste : ";
		}
};

class Dentiste : public Employe{
	string specialite;
	public:
		Dentiste(int m=1,string n="",string t="",string s=""):Employe(m,n,t),specialite(s){;
		}
		string type(){
			return "Dentiste : ";
		}

        float salaire(){return 0;}

        /*float salaire(const Traitement* traitements, int nbrTraitements) {
        double totalPrixTraitements = 0;

        // Parcourir tous les traitements pour calculer la somme des prix pour ce dentiste
        for (int i = 0; i < nbrTraitements; i++) {
            if (traitements[i].getMatr() == getMatricule()) { // getMatricule() vient de Employe
                totalPrixTraitements += traitements[i].getPrix();
            }
        }

        // 60% de la somme des prix des traitements r�alis�s
        return totalPrixTraitements * 0.6;
    }
*/
};



//GESTION EMPLOYE
class GestionEmployes {
private:
    Employe** employes; // Tableau dynamique de pointeurs vers Employe
    int capacity;
    int nbrEmployes;

public:
    GestionEmployes(int cap = 100) : capacity(cap), nbrEmployes(0) {
        employes = new Employe*[capacity]; // Allocation dynamique pour les pointeurs
    }

    ~GestionEmployes() {
        // Lib�rer la m�moire des employ�s
        for (int i = 0; i < nbrEmployes; i++) {
            delete employes[i];
        }
        delete[] employes;
    }

    void ajouterEmploye() {
        if (nbrEmployes >= capacity) {
            cout << "Capacit� maximale atteinte. Impossible d'ajouter un employ�.\n";
            return;
        }

        int type;
        cout << "Entrez le type d'employ� (1: Receptionniste, 2: Assistante, 3: Prothesiste, 4: Dentiste): ";
        cin >> type;

        int matr;
        string nom, tel, specialite;
        float salaire, prime;
        int nbProtheses;

        cout << "Entrez le matricule : ";
        cin >> matr;
        cout << "Entrez le nom : ";
        cin >> nom;
        cout << "Entrez le t�l�phone : ";
        cin >> tel;

        // Cr�er l'employ� selon le type choisi
        if (type == 1) {
            cout << "Entrez le salaire : ";
            cin >> salaire;
            employes[nbrEmployes++] = new Receptionniste(matr, nom, tel, salaire);
        } else if (type == 2) {
            cout << "Entrez le salaire : ";
            cin >> salaire;
            cout << "Entrez la prime : ";
            cin >> prime;
            employes[nbrEmployes++] = new Assistante(matr, nom, tel, salaire, prime);
        } else if (type == 3) {
            cout << "Entrez le salaire par proth�se : ";
            cin >> salaire;
            cout << "Entrez le nombre de proth�ses : ";
            cin >> nbProtheses;
            employes[nbrEmployes++] = new Prothesiste(matr, nom, tel, salaire, nbProtheses);
        } else if (type == 4) {
            cout << "Entrez la sp�cialit� : ";
            cin >> specialite;
            employes[nbrEmployes++] = new Dentiste(matr, nom, tel, specialite);
        } else {
            cout << "Type invalide.\n";
            return;
        }

        cout << "Employ� ajout� avec succ�s.\n";
    }

    void afficherEmployes() const {
        if (nbrEmployes == 0) {
            cout << "Aucun employ� enregistr�.\n";
            return;
        }

        for (int i = 0; i < nbrEmployes; i++) {
            cout << *employes[i];  // Utilisation de l'op�rateur << pour afficher l'employ�
        }
    }

    void supprimerEmploye() {
        int matr;
        cout << "Entrez le matricule de l'employ� � supprimer : ";
        cin >> matr;

        for (int i = 0; i < nbrEmployes; i++) {
            if (employes[i]->getMatricule() == matr) {
                delete employes[i];  // Lib�ration de la m�moire de l'employ� � supprimer
                for (int j = i; j < nbrEmployes - 1; j++) {
                    employes[j] = employes[j + 1]; // D�caler les �l�ments pour supprimer l'employ�
                }
                nbrEmployes--;
                cout << "Employ� supprim� avec succ�s.\n";
                return;
            }
        }
        cout << "Employ� non trouv�.\n";
    }
};



// Classe Patient
class Patient {
private:
    string CIN;
    string nom;
    string prenom;
    string adresse;
    int age;
    string telephone;

public:
    // Constr par d�faut
    Patient() : CIN(""), nom(""), prenom(""), adresse(""), age(0), telephone("") {}

    // Constructeur
    Patient(string c, string n, string p, string a, int ag, string tel)
        : CIN(c), nom(n), prenom(p), adresse(a), age(ag), telephone(tel) {}

    // M�thodes d'affichage d 1 patient
    void afficherPatient() const {
        cout << "-> CIN: " << CIN << endl
             << "-> Nom: " << nom << endl
             << "-> Pr�nom: " << prenom << endl
             << "-> Adresse: " << adresse << endl
             << "-> �ge: " << age << endl
             << "-> T�l�phone: " << telephone << endl
             << endl;
    }

    // Getters et Setters
    string getCin() const { return CIN; }
    void setCin(string c) { CIN = c; }
    string getNom() const { return nom; }
    void setNom(string n) { nom = n; }
    string getPrenom() const { return prenom; }
    void setPrenom(string p) { prenom = p; }
    string getAdresse() const { return adresse; }
    void setAdresse(string a) { adresse = a; }
    int getAge() const { return age; }
    void setAge(int ag) { age = ag; }
    string getTelephone() const { return telephone; }
    void setTelephone(string tel) { telephone = tel; }
};

// Classe pour g�rer les patients
class GestionPatients {
private:
    Patient *patients;
    int capacity;
    int nbrPatients;

public:
    // Constructeur
    GestionPatients(int cap = 100) : capacity(cap), nbrPatients(0) {
        patients = new Patient[capacity];
    }

    // Destructeur
    ~GestionPatients() {
        delete[] patients;
    }

    // Ajouter un patient
    void ajouterPatient() {
        if (nbrPatients >= capacity) {
            cout << "Capacit� maximale atteinte. Impossible d'ajouter un nouveau patient.\n";
            return;
        }
        Patient p;
        string CIN, nom, prenom, adresse, tel;
        int age;

         cout << "Entrez le CIN: ";
         cin >> CIN;

        // V�rifier si le CIN est unique
        for (int i = 0; i < nbrPatients; i++) {
            if (patients[i].getCin() == CIN) {
                cout << "Erreur : un patient avec ce CIN existe d�j�.\n";
                return;
            }
        }

        cout << "Entrez le nom: ";
        cin >> nom;
        cout << "Entrez le pr�nom: ";
        cin >> prenom;
        cout << "Entrez l'adresse: ";
        cin >> adresse;
        //cin.ignore();
        //getline(cin, adresse);
        cout << "Entrez l'�ge: ";
        cin >> age;
        cout << "Entrez le t�l�phone: ";
        cin >> tel;

        // V�rifier si le Tel est unique
        for (int i = 0; i < nbrPatients; i++) {
            if (patients[i].getTelephone() == tel) {
                cout << "Erreur : un patient avec ce tel existe deja.\n";
                return;
            }
        }


        p.setCin(CIN);
        p.setNom(nom);
        p.setPrenom(prenom);
        p.setAdresse(adresse);
        p.setAge(age);
        p.setTelephone(tel);

        patients[nbrPatients++] = p;
        cout << "Patient ajout� avec succ�s.\n";
    }

    // Rechercher un patient
    int rechercherPatient(string CINRecherche) const {
        for (int i = 0; i < nbrPatients; i++) {
            if (patients[i].getCin() == CINRecherche) {
                return i;
            }
        }
        return -1;
    }

    // Modifier un patient
    void modifierPatient() {
        string CINRecherche;
        cout << "Entrez le CIN du patient � modifier : ";
        cin >> CINRecherche;
        int index = rechercherPatient(CINRecherche);
        if (index != -1) {
            string nouvelleAdresse, nouveauTelephone,nouveauNom,nouveauPrenom;
            int nouvelAge;
            cout << "Entrez le nouveau nom : ";
            cin >> nouveauNom;
            cout << "Entrez le nouveau prenom : ";
            cin >> nouveauPrenom;
            cout << "Entrez la nouvelle adresse : ";
            cin >> nouvelleAdresse;
            //cin.ignore();
            //getline(cin, nouvelleAdresse);
            cout << "Entrez le nouveau t�l�phone : ";
            cin >> nouveauTelephone;
            cout << "Entrez le nouvel �ge : ";
            cin >> nouvelAge;

            patients[index].setNom(nouveauNom);
            patients[index].setPrenom(nouveauPrenom);
            patients[index].setAdresse(nouvelleAdresse);
            patients[index].setTelephone(nouveauTelephone);
            patients[index].setAge(nouvelAge);

            cout << "Patient modifi� avec succ�s.\n";
        } else {
            cout << "Patient introuvable.\n";
        }
    }

    // Supprimer un patient
    void supprimerPatient() {
        string CINRecherche;
        cout << "Entrez le CIN du patient � supprimer : ";
        cin >> CINRecherche;
        int index = rechercherPatient(CINRecherche);
        if (index != -1) {
            for (int i = index; i < nbrPatients - 1; i++) {
                patients[i] = patients[i + 1];
            }
            nbrPatients--;
            cout << "Patient supprim� avec succ�s.\n";
        } else {
            cout << "Patient introuvable.\n";
        }
    }

    // Afficher tous les patients
    void afficherTousLesPatients() const {
        if (nbrPatients == 0) {
            cout << "Aucun patient dans la base de donn�es.\n";
        } else {
            for (int i = 0; i < nbrPatients; i++) {
                cout << "*** Patient " << i + 1 << " *** :\n";
                patients[i].afficherPatient();
                cout << "-----------------------------\n";
            }
        }
    }

    //Vrification du Compatibilit� du CIN
    bool verifierCIN(string CIN) const {
        for (int i = 0; i < nbrPatients; i++) {
            if (patients[i].getCin() == CIN) {
                return true;
            }
        }
        return false;
    }
};

// Classe RendezVous
class RendezVous {
private:
    int idRdv;
    string CINPatient;
    int idDentiste;
    Date dateRdv;
    Time heureRdv;

public:
    RendezVous() : idRdv(0), CINPatient(""), idDentiste(0), dateRdv(Date()), heureRdv(0, 0) {}
    RendezVous(int id, string cin, int idD, Date date, Time heure)
        : idRdv(id), CINPatient(cin), idDentiste(idD), dateRdv(date), heureRdv(heure) {}


    void afficherRendezVous() const {
        cout << "ID Rendez-vous: " << idRdv << endl;
        cout << "CIN Patient: " << CINPatient << endl;
        cout << "ID Dentiste: " << idDentiste << endl;
        cout << "Date: ";
        dateRdv.afficherDate();
        cout << endl;
        cout << "Heure: " << heureRdv << endl;
    }


    int getIdRdv() const { return idRdv; }
    void setIdRdv(int id) { idRdv = id; }
    string getCINPatient() const { return CINPatient; }
    void setCINPatient(string cin) { CINPatient = cin; }
    int getIdDentiste() const { return idDentiste; }
    void setIdDentiste(int id) { idDentiste = id; }
    Date getDateRdv() const { return dateRdv; }
    void setDateRdv(Date date) { dateRdv = date; }
    Time getHeureRdv() const { return heureRdv; }
    void setHeureRdv(Time heure) { heureRdv = heure; }
};

// Classe GestionRendezVous avec tableau dynamique
class GestionRendezVous {
private:
    RendezVous* rdvs;
    int capacity;
    int nbrRdvs;

public:
    GestionRendezVous(int cap = 100) : capacity(cap), nbrRdvs(0) {
        rdvs = new RendezVous[capacity];
    }

    ~GestionRendezVous() {
        delete[] rdvs;
    }

    void ajouterRendezVous(const GestionPatients& gestionPatients) {
        if (nbrRdvs >= capacity) {
            cout << "Capacit� maximale atteinte. Impossible d'ajouter un nouveau rendez-vous.\n";
            return;
        }

        int idRdv, idDentiste;
        string CINPatient;
        int jour, mois, annee;
        Time heureRdv(0, 0);

        cout << "Entrez l'ID du rendez-vous: ";
        cin >> idRdv;

        // V�rification de l'unicit� de l'ID du rendez-vous
        for (int i = 0; i < nbrRdvs; i++) {
            if (rdvs[i].getIdRdv() == idRdv) {
                cout << "Erreur : Un rendez-vous avec cet ID existe deja.\n";
                return;
            }
        }

        cout << "Entrez le CIN du patient: ";
        cin >> CINPatient;

        if (!gestionPatients.verifierCIN(CINPatient)) {
            cout << "Erreur : Aucun patient avec ce CIN trouve, veillez l'ajoute.\n";
            return;
        }
        cout << "Entrez l'ID du dentiste: ";
        cin >> idDentiste;
        cout << "Entrez la date (jour mois ann�e): ";
        cin >> jour >> mois >> annee;
        cout << "Entrez l'heure (heure et minutes): ";
        cin >> heureRdv;

        // Utilisation de jour, mois, annee pour cr�er un objet Date
        rdvs[nbrRdvs++] = RendezVous(idRdv, CINPatient, idDentiste, Date(jour, mois, annee), heureRdv);
        cout << "Rendez-vous ajout� avec succ�s.\n";
    }

    void modifierRendezVous() {
        int idRecherche;
        int jour, mois, annee;
        Time nouvelleHeure(0, 0);

        cout << "Entrez l'ID du rendez-vous � modifier: ";
        cin >> idRecherche;

        int index = rechercherRendezVous(idRecherche);
        if (index != -1) {
            cout << "Entrez la nouvelle date (jour mois ann�e): ";
            cin >> jour >> mois >> annee;
            cout << "Entrez la nouvelle heure (heure et minutes): ";
            cin >> nouvelleHeure;

            // Modifie la date avec les nouvelles valeurs
            rdvs[index].setDateRdv(Date(jour, mois, annee));
            rdvs[index].setHeureRdv(nouvelleHeure);
            cout << "Rendez-vous modifi� avec succ�s.\n";
        } else {
            cout << "Rendez-vous introuvable.\n";
        }
    }

    void supprimerRendezVous() {
        int idRecherche;
        cout << "Entrez l'ID du rendez-vous � supprimer: ";
        cin >> idRecherche;

        int index = rechercherRendezVous(idRecherche);
        if (index != -1) {
            for (int i = index; i < nbrRdvs - 1; i++) {
                rdvs[i] = rdvs[i + 1];
            }
            nbrRdvs--;
            cout << "Rendez-vous supprim� avec succ�s.\n";
        } else {
            cout << "Rendez-vous introuvable.\n";
        }
    }

    void afficherTousLesRendezVous() const {
        if (nbrRdvs == 0) {
            cout << "Aucun rendez-vous dans la base de donn�es.\n";
        } else {
            for (int i = 0; i < nbrRdvs; i++) {
                cout << "Rendez-vous " << i + 1 << ":\n";
                rdvs[i].afficherRendezVous();
                cout << "-----------------------------\n";
            }
        }
    }

    int rechercherRendezVous(int idRecherche) const {
        for (int i = 0; i < nbrRdvs; i++) {
            if (rdvs[i].getIdRdv() == idRecherche) {
                return i;
            }
        }
        return -1;
    }

    void afficherRendezVousPatient(const GestionPatients& gestionPatients) const {
    string CIN;
    cout << "Entrez le CIN du patient : ";
    cin >> CIN;

    // V�rifie si le CIN existe dans la liste des patients
    if (!gestionPatients.verifierCIN(CIN)) {
        cout << "Erreur : Aucun patient avec ce CIN trouv�.\n";
        return;
    }

    // V�rifie si des rendez-vous sont enregistr�s
    if (nbrRdvs == 0) {
        cout << "Aucun rendez-vous enregistr�.\n";
        return;
    }

    // Affiche les rendez-vous qui correspondent au CIN
    bool rendezVousTrouve = false;
    for (int i = 0; i < nbrRdvs; i++) {
        if (rdvs[i].getCINPatient() == CIN) {
            cout << "*** Rendez-vous " << i + 1 << " ***\n";
            rdvs[i].afficherRendezVous();
            cout << "-----------------------------\n";
            rendezVousTrouve = true;
        }
    }

    // Si aucun rendez-vous n'est trouv� pour le CIN
    if (!rendezVousTrouve) {
        cout << "Aucun rendez-vous trouv� pour ce patient.\n";
    }
}

};



// Classe Traitement
class Traitement {
private:
    string CIN;
    int matr;
    int numDent;
    string acte;
    string remarque;
    double prix;
    Date date;

public:
    Traitement() : CIN(""),matr(0), numDent(0), acte(""), remarque(""), prix(0.0), date(Date()) {}

    Traitement(string c, int m , int num, string a, string r, double p, Date d)
        : CIN(c),matr(m), numDent(num), acte(a), remarque(r), prix(p), date(d) {}

    void afficherTraitement() const {
        cout << "CIN du patient : " << CIN << endl;
        cout << "Matricule du dentiste : " << matr << endl;
        cout << "Date : ";
        date.afficherDate() ;
        cout << endl;
        cout << "Num�ro de dent : " << numDent << endl;
        cout << "Acte : " << acte << endl;
        cout << "Remarque : " << remarque << endl;
        cout << "Prix : " << prix << " DH\n";
    }

    int getMatr() const { return matr; }
    double getPrix() const { return prix; }
    string getCIN() const { return CIN; }
    int getNumDent() const { return numDent; }
    void setTraitement(string a, string r, double p, Date d) {
        acte = a;
        remarque = r;
        prix = p;
        date = d;
    }
};

// Classe pour g�rer les traitements
class GestionTraitements {
private:
    Traitement* traitements;
    int capacity;
    int nbrTraitements;

public:
    GestionTraitements(int cap = 100) : capacity(cap), nbrTraitements(0) {
        traitements = new Traitement[capacity];
    }

    ~GestionTraitements() {
        delete[] traitements;
    }

    void ajouterTraitement(const GestionPatients& gestionPatients) {
        if (nbrTraitements >= capacity) {
            cout << "Capacit� maximale atteinte. Impossible d'ajouter un nouveau traitement.\n";
            return;
        }


        string CIN, acte, remarque;
        int matr, numDent, jour, mois, annee;
        double prix;

        cout << "Entrez le CIN du patient : ";
        cin >> CIN;

        if (!gestionPatients.verifierCIN(CIN)) {
            cout << "Erreur : Aucun patient avec ce CIN trouve, veillez l'ajoute.\n";
            return;
        }
        cout << "Entrez le matricule du dentiste : ";
        cin >> matr;
        cout << "Entrez la date (jour mois ann�e) : ";
        cin >> jour >> mois >> annee;
        cout << "Entrez le num�ro de dent : ";
        cin >> numDent;
        cout << "Entrez le type d'acte : ";
        cin >> acte;
        cout << "Entrez la remarque : ";
        cin >> remarque;
        cout << "Entrez le prix : ";
        cin >> prix;

        traitements[nbrTraitements++] = Traitement(CIN,matr, numDent, acte, remarque, prix, Date(jour, mois, annee));
        cout << "Traitement ajout� avec succ�s.\n";
    }

    void modifierTraitement() {
        string CIN;
        int numDent;

        cout << "Entrez le CIN du patient : ";
        cin >> CIN;

        cout << "Entrez le num�ro de dent : ";
        cin >> numDent;

        for (int i = 0; i < nbrTraitements; i++) {
            if (traitements[i].getCIN() == CIN && traitements[i].getNumDent() == numDent) {
                string acte, remarque;
                double prix;
                int jour, mois, annee;

                cout << "Entrez le nouveau type d'acte : ";
                cin >> acte;
                cout << "Entrez la nouvelle remarque : ";
                cin >> remarque;
                cout << "Entrez le nouveau prix : ";
                cin >> prix;
                cout << "Entrez la nouvelle date (jour mois ann�e) : ";
                cin >> jour >> mois >> annee;

                traitements[i].setTraitement(acte, remarque, prix, Date(jour, mois, annee));
                cout << "Traitement modifi� avec succ�s.\n";
                return;
            }
        }

        cout << "Traitement introuvable.\n";
    }

    void supprimerTraitement() {
        string CIN;
        int numDent;

        cout << "Entrez le CIN du patient : ";
        cin >> CIN;

        cout << "Entrez le num�ro de dent : ";
        cin >> numDent;

        for (int i = 0; i < nbrTraitements; i++) {
            if (traitements[i].getCIN() == CIN && traitements[i].getNumDent() == numDent) {
                for (int j = i; j < nbrTraitements - 1; j++) {
                    traitements[j] = traitements[j + 1];
                }
                nbrTraitements--;
                cout << "Traitement supprim� avec succ�s.\n";
                return;
            }
        }

        cout << "Traitement introuvable.\n";
    }

    void afficherTousLesTraitements() const {

        if (nbrTraitements == 0) {
            cout << "Aucun traitement enregistr�.\n";
        } else {
            for (int i = 0; i < nbrTraitements; i++) {
                cout << "*** Traitement " << i + 1 << " ***\n";
                traitements[i].afficherTraitement();
                cout << "-----------------------------\n";
            }
        }
    }

    //affichage de tous les traitements d'un patient
    void afficherTraitementsPatient(const GestionPatients& gestionPatients) const {
            string CIN;
            cout << "Entrez le CIN du patient : ";
            cin >> CIN;

            // V�rifie si le CIN existe dans la liste des patients
            if (!gestionPatients.verifierCIN(CIN)) {
                cout << "Erreur : Aucun patient avec ce CIN trouv�.\n";
                return;
            }

            // V�rifie si des traitements sont enregistr�s
            if (nbrTraitements == 0) {
                cout << "Aucun traitement enregistr�.\n";
                return;
            }

            // Affiche les traitements qui correspondent au CIN
            bool traitementTrouve = false;
            for (int i = 0; i < nbrTraitements; i++) {
                if (traitements[i].getCIN() == CIN) {
                    cout << "*** Traitement " << i + 1 << " ***\n";
                    traitements[i].afficherTraitement();
                    cout << "-----------------------------\n";
                    traitementTrouve = true;
                }
            }

            // Si aucun traitement n'est trouv� pour le CIN
            if (!traitementTrouve) {
                cout << "Aucun traitement trouv� pour ce patient.\n";
            }
}



};


int main() {
    // Instances pour la gestion des diff�rentes entit�s
    GestionPatients gestion; // Gestion des patients
    GestionTraitements gestionTraitements; // Gestion des traitements
    GestionRendezVous gestionRendezVous; // Gestion des rendez-vous
    GestionEmployes gestionEmployes; // Gestion des employ�s
    int choix;

    do {
        // Menu principal avec une option pour la gestion des employ�s
        cout << "\n=== Menu G�n�ral ===\n";
        cout << "1. Ajouter un patient\n";
        cout << "2. Modifier un patient\n";
        cout << "3. Supprimer un patient\n";
        cout << "4. Afficher tous les patients\n";
        cout << "5. Ajouter un traitement\n";
        cout << "6. Modifier un traitement\n";
        cout << "7. Supprimer un traitement\n";
        cout << "8. Afficher tous les traitements\n";
        cout << "9. Afficher tous les traitements d'un patient\n";
        cout << "10. Ajouter un rendez-vous\n";
        cout << "11. Modifier un rendez-vous\n";
        cout << "12. Supprimer un rendez-vous\n";
        cout << "13. Afficher tous les rendez-vous\n";
        cout << "14. Afficher tous les rendez-vous d'un patient\n";
        cout << "15. Gestion des employ�s\n"; // Nouvelle option pour g�rer les employ�s
        cout << "0. Quitter\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            // Gestion des patients
            case 1:
                gestion.ajouterPatient();
                break;
            case 2:
                gestion.modifierPatient();
                break;
            case 3:
                gestion.supprimerPatient();
                break;
            case 4:
                gestion.afficherTousLesPatients();
                break;

            // Gestion des traitements
            case 5:
                gestionTraitements.ajouterTraitement(gestion);
                break;
            case 6:
                gestionTraitements.modifierTraitement();
                break;
            case 7:
                gestionTraitements.supprimerTraitement();
                break;
            case 8:
                gestionTraitements.afficherTousLesTraitements();
                break;
            case 9:
                gestionTraitements.afficherTraitementsPatient(gestion);
                break;

            // Gestion des rendez-vous
            case 10:
                gestionRendezVous.ajouterRendezVous(gestion);
                break;
            case 11:
                gestionRendezVous.modifierRendezVous();
                break;
            case 12:
                gestionRendezVous.supprimerRendezVous();
                break;
            case 13:
                gestionRendezVous.afficherTousLesRendezVous();
                break;
            case 14:
                gestionRendezVous.afficherRendezVousPatient(gestion);
                break;

            // Gestion des employ�s
            case 15:
                int choixEmploye;
                do {
                    cout << "\n=== Gestion des Employ�s ===\n";
                    cout << "1. Ajouter un employ�\n";
                    cout << "2. Afficher tous les employ�s\n";
                    cout << "3. Supprimer un employ�\n";
                    cout << "0. Retour au menu principal\n";
                    cout << "Votre choix : ";
                    cin >> choixEmploye;

                    switch (choixEmploye) {
                        case 1:
                            gestionEmployes.ajouterEmploye();  // Ajouter un employ�
                            break;
                        case 2:
                            gestionEmployes.afficherEmployes();  // Afficher tous les employ�s
                            break;
                        case 3:
                            gestionEmployes.supprimerEmploye();  // Supprimer un employ�
                            break;
                        case 0:
                            break;  // Retour au menu principal
                        default:
                            cout << "Choix invalide. Veuillez r�essayer.\n";
                    }
                } while (choixEmploye != 0);
                break;

            // Quitter
            case 0:
                cout << "Au revoir !\n";
                break;

            // Choix invalide
            default:
                cout << "Choix invalide. Veuillez r�essayer.\n";
        }
    } while (choix != 0);

    return 0;
}

