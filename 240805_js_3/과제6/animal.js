class Animal {
  name;
  constructor(name) {
    this.name = name;
  }
  speak() {
    console.log(`${this.name}이 소리를 내며 짖습니다.`);
  }
}

class Cat extends Animal {
  speak() {
    console.log(`${this.name}이 야옹 소리를 냅니다.`);
  }
}

class Dog extends Animal {
  speak() {
    console.log(`${this.name}이 멍멍 소리를 냅니다.`);
  }
}

const animal = new Animal("동물");
animal.speak();

const cat = new Cat("캣");
cat.speak();

const dog = new Dog("독");
dog.speak();
