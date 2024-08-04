class Student {
  name;
  age;
  greeting;
  constructor(name, age, greeting) {
    this.name = name;
    this.age = age;
    this.greeting = greeting;
  }
  introduce() {
    console.log(`이름: ${this.name}`);
    console.log(`나이: ${this.age}`);
    console.log(`자기소개: ${this.greeting}`);
  }
}

const student = new Student("최지웅", 26, "방가루");
student.introduce();
