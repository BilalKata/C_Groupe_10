CREATE DATABASE Voiture;
USE Voiture;

CREATE TABLE Marque(
   id INT UNSIGNED NOT NULL,
   name VARCHAR(70) NOT NULL,
   niceName VARCHAR(70) NOT NULL,
   PRIMARY KEY(id),
   UNIQUE(name)
);

CREATE TABLE Modele(
   id VARCHAR(70) NOT NULL,
   name VARCHAR(70) NOT NULL,
   niceName VARCHAR(70) NOT NULL,
   makeId INT UNSIGNED NOT NULL,
   PRIMARY KEY( niceName),
   UNIQUE(id, name),
   FOREIGN KEY(makeId) REFERENCES Marque(id)
);

CREATE TABLE Version(
   id INT UNSIGNED NOT NULL,
   name VARCHAR(70) NOT NULL,
   versionPower SMALLINT NOT NULL,
   modelNiceName VARCHAR(70) NOT NULL,
   PRIMARY KEY(id),
   UNIQUE(name),
   FOREIGN KEY(modelNiceName) REFERENCES Modele(niceName)
);
