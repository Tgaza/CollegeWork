
public abstract class Pet {
	private String petName;
	private PetType petType;
	
	public Pet(String petName, PetType petType) {
		this.petName = petName;
		this.petType = petType;
	}
	
	public abstract void makeNoise();
	public abstract void giveTreat();
	public abstract void fun();
	
	public String getName() {
		return this.petName;
	}
	
	public PetType petType() {
		return this.petType;
	}
}
