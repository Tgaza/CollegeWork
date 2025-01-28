import java.util.ArrayList;

public class Bill {
	private ArrayList<Item> listsOfItems;
	private long tax;
	private long total;
	
	public Bill(ArrayList<Item> listsOfItems, long tax) {
		this.listsOfItems = listsOfItems;
		this.tax = tax;
		this.total = 0;
		for (Item item : listsOfItems) {
			total += item.getPrice();
		}
		total += tax;
	}
	
	public long getTotal() {
		return total;
	}
	
	public void setTotal(long total) {
		this.total = total;
	}

	public long getTax() {
		return tax;
	}

	public ArrayList<Item> getListsOfItems() {
		return listsOfItems;
	}
	
}
