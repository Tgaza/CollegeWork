import java.util.ArrayList;

public class PetStore {
	private ArrayList<Pet> pets = new ArrayList<Pet>();
	
	public void sounds() {
		for (Pet pet : pets) {
			pet.makeNoise();
		}	
		System.out.println() ;
	}
	
	public void treats() {
		for (Pet pet : pets) {
			pet.giveTreat();
		}
		System.out.println() ;
	}
	
	public void fun() {
		for (Pet pet : pets) {
			pet.fun();
		}	
		System.out.println() ;
	}
	
	public void addPet( Pet pet ) {
		pets.add( pet ) ;
	}

	public void listPets() {
		for( Pet pet : pets ) {
			System.out.println(pet);
		}
	}
	
	public static void main(String[] args) {
		PetStore myStore = new PetStore() ;
		
		myStore.addPet(new Cat("Buttons", PetType.CAT ));
		myStore.addPet(new Dog("Boxer", PetType.DOG ));
		myStore.addPet(new Cat("Dax", PetType.CAT ));
		myStore.addPet(new Horse("Betty", PetType.HORSE ));
		
		myStore.fun();
		myStore.treats();
		myStore.sounds();
		
	}

}
