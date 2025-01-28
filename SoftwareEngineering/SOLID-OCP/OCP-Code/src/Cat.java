
public class Cat extends Pet {

	public Cat(String petName, PetType petType) {
		super(petName, petType);
	}

	@Override
	public void makeNoise() {
		System.out.println("Meow");
	}

	@Override
	public void giveTreat() {
		System.out.println("Give " + this.getName() + " some catnip");
	}

	@Override
	public void fun() {
		System.out.println("Watch " + this.getName() + " sleep");
	}

}
