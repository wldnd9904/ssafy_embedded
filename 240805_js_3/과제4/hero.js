class Hero {
  #hp = 100;
  showHP() {
    console.log(this.#hp);
  }
  run() {
    this.#hp -= 10;
  }
}

const hero = new Hero();
hero.showHP();
hero.run();
hero.run();
hero.showHP();
