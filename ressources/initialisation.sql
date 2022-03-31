CREATE DATABASE Voiture;
USE Voiture;

CREATE TABLE Marque(
   id SMALLINT,
   name VARCHAR(50) NOT NULL,
   niceName VARCHAR(50) NOT NULL,
   PRIMARY KEY(id),
   UNIQUE(name)
);

CREATE TABLE Utilsateur(
   nomUtilisateur VARCHAR(50),
   motDePasse VARCHAR(255) NOT NULL,
   PRIMARY KEY(nomUtilisateur)
);

CREATE TABLE Administrateur(
   nomAdministrateur VARCHAR(50),
   motdePasse VARCHAR(255) NOT NULL,
   PRIMARY KEY(nomAdministrateur)
);

CREATE TABLE Modele(
   id SMALLINT,
   name VARCHAR(50) NOT NULL,
   niceName VARCHAR(50) NOT NULL,
   makeId SMALLINT NOT NULL,
   PRIMARY KEY(id),
   UNIQUE(name),
   FOREIGN KEY(makeId) REFERENCES Marque(id)
);

CREATE TABLE Version(
   id SMALLINT,
   name VARCHAR(50) NOT NULL,
   versionPower SMALLINT NOT NULL,
   modelNiceName SMALLINT NOT NULL,
   PRIMARY KEY(id),
   UNIQUE(name),
   FOREIGN KEY(modelNiceName) REFERENCES Modele(id)
);

CREATE TABLE consulte(
   id SMALLINT,
   nomUtilisateur VARCHAR(50),
   PRIMARY KEY(id, nomUtilisateur),
   FOREIGN KEY(id) REFERENCES Marque(id),
   FOREIGN KEY(nomUtilisateur) REFERENCES Utilsateur(nomUtilisateur)
);

CREATE TABLE gere(
   id SMALLINT,
   nomAdministrateur VARCHAR(50),
   PRIMARY KEY(id, nomAdministrateur),
   FOREIGN KEY(id) REFERENCES Marque(id),
   FOREIGN KEY(nomAdministrateur) REFERENCES Administrateur(nomAdministrateur)
);

CREATE TABLE administre(
   nomUtilisateur VARCHAR(50),
   nomAdministrateur VARCHAR(50),
   PRIMARY KEY(nomUtilisateur, nomAdministrateur),
   FOREIGN KEY(nomUtilisateur) REFERENCES Utilsateur(nomUtilisateur),
   FOREIGN KEY(nomAdministrateur) REFERENCES Administrateur(nomAdministrateur)
);