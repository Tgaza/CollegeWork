
public class Report {
	private String reportType;
	private String name;
	private long bill;


	public Report(String reportType, String name, long bill) {
		this.reportType = reportType;
		this.name = name;
		this.bill = bill;
	}
	
	public void displayReport() {
		if (reportType.equalsIgnoreCase("CSV")) {
			System.out.println("CSV Report: " + name + "'s bill is " + bill);
		}
		if (reportType.equalsIgnoreCase("XML")) {
			System.out.println("XML Report: " + name + "'s bill is " + bill);
		}
	}
}
