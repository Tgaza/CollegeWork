
public class Horse extends Pet {

	public Horse(String petName, PetType petType) {
		super(petName, petType);
	}

	@Override
	public void makeNoise() {
		System.out.println("Neighhh");
	}

	@Override
	public void giveTreat() {
		System.out.println("Give " + this.getName() + " an apple");
	}

	@Override
	public void fun() {
		System.out.println("Ride " + this.getName() + " around the farm");

	}

}
