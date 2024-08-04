class Person {
  name;
  hp;

  constructor(name, hp) {
    this.name = name;
    this.hp = hp;
  }

  hello() {
    console.log(this.name);
  }
}

class Avengers extends Person {
  power;
  skill;

  constructor(name, hp, power, skill) {
    super(name, hp);
    this.power = power;
    this.skill = skill;
  }

  information() {
    console.log(`이름: ${this.name}`);
    console.log(`HP: ${this.hp}`);
    console.log(`전투력: ${this.power}`);
    console.log(`능력: ${this.skill}`);
  }

  fly() {
    console.log("비행중...");
  }
}

const ironMan = new Avengers("아이언맨", 100, 10000, "미사일");
ironMan.information();
ironMan.fly();
