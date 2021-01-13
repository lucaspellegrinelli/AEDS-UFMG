CREATE TABLE Pokemon (
  id_pokemon INT NOT NULL,
  nome VARCHAR(50) NOT NULL,
  descricao VARCHAR(300)
  PRIMARY KEY (id_pokemon)
);

CREATE TABLE TipoPokemon (
  id_pokemon INT NOT NULL,
  tipo VARCHAR(10) NOT NULL,
  FOREIGN KEY (id_pokemon) REFERENCES Pokemon(id_pokemon)
);

CREATE TABLE UsoPokemon (
  id_pokemon INT NOT NULL,
  ano INT NOT NULL,
  mes INT NOT NULL,
  porcentagem FLOAT NOT NULL,
  FOREIGN KEY (id_pokemon) REFERENCES Pokemon(id_pokemon)
);

CREATE TABLE Evolucao (
  id_de INT NOT NULL,
  id_para INT NOT NULL,
  grau INT NOT NULL,
  FOREIGN KEY (id_de) REFERENCES Pokemon(id_pokemon),
  FOREIGN KEY (id_para) REFERENCES Pokemon(id_pokemon)
);

CREATE TABLE AliadosComuns (
  id_pokemon INT NOT NULL,
  id_aliado INT NOT NULL,
  ano INT NOT NULL,
  mes INT NOT NULL,
  porcentagem FLOAT NOT NULL,
  FOREIGN KEY (id_pokemon) REFERENCES Pokemon(id_pokemon),
  FOREIGN KEY (id_aliado) REFERENCES Pokemon(id_pokemon)
);

CREATE TABLE Ataque (
  id_ataque INT NOT NULL,
  nome VARCHAR(50),
  descricao VARCHAR(300),
  tipo VARCHAR(10),
  PRIMARY KEY (id_ataque)
);

CREATE TABLE UsoAtaque (
  id_pokemon INT NOT NULL,
  id_ataque INT NOT NULL,
  ano INT NOT NULL,
  mes INT NOT NULL,
  percentagem FLOAT NOT NULL,
  FOREIGN KEY (id_pokemon) REFERENCES Pokemon(id_pokemon),
  FOREIGN KEY (id_ataque) REFERENCES Ataque(id_ataque)
);

CREATE TABLE Habilidade (
  id_habilidade INT NOT NULL,
  nome VARCHAR(50),
  descricao VARCHAR(300),
  PRIMARY KEY (id_habilidade)
);

CREATE TABLE UsoHabilidade (
  id_pokemon INT NOT NULL,
  id_habilidade INT NOT NULL,
  ano INT NOT NULL,
  mes INT NOT NULL,
  percentagem FLOAT NOT NULL,
  FOREIGN KEY (id_pokemon) REFERENCES Pokemon(id_pokemon),
  FOREIGN KEY (id_habilidade) REFERENCES Habilidade(id_habilidade)
)
