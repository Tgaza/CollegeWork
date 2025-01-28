
import java.util.ArrayList;

public class Customer {

	private String name;
	private int age;
	private Bill bill;
	private ArrayList<Item> listsOfItems;

	public Customer(String name, int age) {
		this.name = name;
		this.age = age;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	
	public Bill getBill() {
		return this.bill;
	}
	
	public void setBill(Bill newBill) {
		this.bill = newBill;
	}

	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public ArrayList<Item> getListsOfItems() {
		return listsOfItems;
	}

	public void setListsOfItems(ArrayList<Item> listsOfItems) {
		this.listsOfItems = listsOfItems;
	}

	public static void main(String[] args) {
		ArrayList<Item> items = new ArrayList<Item>();

		items.add(new Item(25));
		items.add(new Item(45));

		Customer fred = new Customer("Fred", 25);
		fred.setListsOfItems(items);
		Bill fredsBill = new Bill(fred.getListsOfItems(), 10);
		fred.setBill(fredsBill);
		Report fredsReport = new Report("CSV", fred.getName(), fredsBill.getTotal());
		fredsReport.displayReport();
		
		Customer karen = new Customer( "Karen", 30 ) ;
		items.clear() ;
		items.add(new Item(10));
		items.add(new Item(10));
		karen.setListsOfItems(items);
		Bill karensBill = new Bill(karen.getListsOfItems(), 20);
		karen.setBill(karensBill);
		Report karensReport = new Report("XML", karen.getName(), karensBill.getTotal());
		karensReport.displayReport();

	}

}