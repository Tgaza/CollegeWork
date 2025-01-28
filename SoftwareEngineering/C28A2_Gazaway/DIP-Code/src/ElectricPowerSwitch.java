import java.util.ArrayList;

public class ElectricPowerSwitch {
	public ArrayList<Switchable> appliances;
	public boolean on;

	public ElectricPowerSwitch(ArrayList<Switchable> appliances) {
		this.appliances = appliances;
		this.on = false;
	}

	public boolean isOn() {
		return this.on;
	}

	public void press() {
		boolean checkOn = isOn();
		if (checkOn) {
			for (Switchable appliance : appliances) {
				appliance.turnOff();
			}
			this.on = false;
		} else {
			for (Switchable appliance : appliances) {
				appliance.turnOn();
			}
			this.on = true;
		}
	}
}