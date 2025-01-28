import java.util.ArrayList;

public class Control {
	public static void main(String[] args) {
		LightBulb lightBulb = new LightBulb();
		Fan fan = new Fan();
		ArrayList<Switchable> appliances = new ArrayList<>();
		appliances.add(lightBulb);
		appliances.add(fan);
		ElectricPowerSwitch bulbSwitch = new ElectricPowerSwitch(appliances);

		bulbSwitch.press();
		bulbSwitch.press();
	}
}
