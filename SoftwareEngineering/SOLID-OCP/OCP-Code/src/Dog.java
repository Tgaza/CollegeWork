
public class Dog extends Pet {

	public Dog(String petName, PetType petType) {
		super(petName, petType);
	}

	@Override
	public void makeNoise() {
		System.out.println("Woof");
	}

	@Override
	public void giveTreat() {
		System.out.println("Give " + this.getName() + " a bone");
	}

	@Override
	public void fun() {
		System.out.println("Throw a frisbee to " + this.getName());
	}

}
