import tkinter as tk
from tkinter import messagebox, Toplevel, Checkbutton, IntVar
from datetime import datetime, timedelta
import random
from tkinter import ttk

# --- Abstract Fault Class ---
class Fault:
    def __init__(self, name, description, repair_time, severity):
        self._name = name
        self._description = description
        self._repair_time = repair_time  # in hours
        self._severity = severity

    def calculate_repair_time(self):
        # Repair time can be influenced by severity
        return self._repair_time + (self._severity * 0.5)

    def __str__(self):
        return f"{self._name}: {self._description} (Repair Time: {self.calculate_repair_time()} hours)"


# --- Fault Classes ---
class PassengerInfoFault(Fault):
    def __init__(self):
        super().__init__("Passenger Information Fault", "Issues with the passenger information system.", 5, 5)

class FireDetectionFault(Fault):
    def __init__(self):
        super().__init__("Fire Detection Fault", "Fire detection system malfunction.", 8, 2)

class ToiletSystemFault(Fault):
    def __init__(self):
        super().__init__("Toilet System Fault", "Toilets are out of order.", 3, 4)

class LightingFault(Fault):
    def __init__(self):
        super().__init__("Lighting Fault", "Lighting system is malfunctioning.", 4, 5)

class BogieFault(Fault):
    def __init__(self):
        super().__init__("Bogie Fault", "Issues with the bogie system.", 10, 1)

class DoorFault(Fault):
    def __init__(self):
        super().__init__("Door Fault", "Doors are malfunctioning.", 7, 2)

class TCMSCommunicationFault(Fault):
    def __init__(self):
        super().__init__("TCMS Communication Fault", "Communication issues in the TCMS.", 9, 1)

class AirConditioningFault(Fault):
    def __init__(self):
        super().__init__("Air Conditioning Fault", "Air conditioning system failure.", 6, 4)

class WheelsetFault(Fault):
    def __init__(self):
        super().__init__("Wheelset Fault", "Issues with the wheelset detected.", 7, 2)

class BrakeSystemFault(Fault):
    def __init__(self):
        super().__init__("Brake System Fault", "Brakes are malfunctioning.", 10, 1)

class ElectricalFault(Fault):
    def __init__(self):
        super().__init__("Electrical Fault", "Electrical systems are failing.", 6, 3)

class FuelSystemFault(Fault):
    def __init__(self):
        super().__init__("Fuel System Fault", "Fuel system malfunction.", 8, 2)

class EngineFault(Fault):
    def __init__(self):
        super().__init__("Engine Fault", "Engine issues detected.", 12, 2)

class TransmissionFault(Fault):
    def __init__(self):
        super().__init__("Transmission Fault", "Transmission system failure.", 9, 2)

class CoolingSystemFault(Fault):
    def __init__(self):
        super().__init__("Cooling System Fault", "Cooling system malfunction.", 8, 4)

class HydraulicSystemFault(Fault):
    def __init__(self):
        super().__init__("Hydraulic System Fault", "Hydraulic system issues.", 7, 4)

class SuspensionFault(Fault):
    def __init__(self):
        super().__init__("Suspension Fault", "Suspension system failure.", 6, 3)

class SignalSystemFault(Fault):
    def __init__(self):
        super().__init__("Signal System Fault", "Signal system error.", 6, 1)

class BatteryFault(Fault):
    def __init__(self):
        super().__init__("Battery Fault", "Battery issues detected.", 4, 3)


# --- Abstract Train Class ---
class Train:
    def __init__(self, train_number, train_type):
        self._train_number = train_number
        self._train_type = train_type
        self._faults = []
        self._estimated_completion = None
        self._status = "In Maintenance"
       

    def add_fault(self, fault):
        self._faults.append(fault)
        self.calculate_completion_time()

    def calculate_completion_time(self):
        total_hours = sum(fault.calculate_repair_time() for fault in self._faults)
        self._estimated_completion = datetime.now() + timedelta(hours=total_hours)

    def mark_as_repaired(self):
        self._status = "Repaired"
        self._faults = []

    def get_train_status(self):
        return self._status

    def get_faults(self):
        return self._faults

    def get_estimated_completion(self):
        return self._estimated_completion.strftime("%Y-%m-%d %H:%M:%S") if self._estimated_completion else "Not calculated"

    def __str__(self):
        faults_description = "\n".join(str(fault) for fault in self._faults)
        completion_time = self.get_estimated_completion()
        return (
            f"Train Number: {self._train_number}\n"
            f"Train Type: {self._train_type}\n"
            f"Faults:\n{faults_description if self._faults else 'No faults'}\n"
            f"Estimated Completion: {completion_time}\n"
            f"Status: {self._status}"
        )


# --- Train Types ---
class HighSpeedTrain(Train):
    def __init__(self, train_number):
        super().__init__(train_number, "High Speed")


class FreightTrain(Train):
    def __init__(self, train_number):
        super().__init__(train_number, "Freight")


# --- GUI Class ---
class MaintenanceApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Train Maintenance Tracker")
        self.trains = []

        # Train List
        self.train_listbox = tk.Listbox(root, width=80, height=15)
        self.train_listbox.pack(pady=10)

             # Train Number and Add Train Button
        train_frame = tk.Frame(root)
        train_frame.pack(pady=5)

        self.train_number_label = tk.Label(train_frame, text="Train Number:")
        self.train_number_label.pack(side=tk.LEFT, padx=5)

        self.train_number_entry = tk.Entry(train_frame)
        self.train_number_entry.pack(side=tk.LEFT, padx=5)

        self.add_train_button = tk.Button(
            train_frame, text="Add Train", command=self.add_train, bg="lightblue", fg="black"
        )
        self.add_train_button.pack(side=tk.LEFT, padx=5)

        # Create a frame for other buttons
        button_frame = tk.Frame(root)
        button_frame.pack(pady=5)

        # Add Fault Button
        self.add_fault_button = tk.Button(
            button_frame, text="Add Fault to Selected Train", command=self.show_fault_selection, bg="lightgreen", fg="black"
        )
        self.add_fault_button.pack(side=tk.LEFT, padx=5)

        # View Train Details Button
        self.view_details_button = tk.Button(
            button_frame, text="View Fault Details", command=self.view_details, bg="yellow", fg="black"
        )
        self.view_details_button.pack(side=tk.LEFT, padx=5)

        # Mark as Repaired Button
        self.mark_repaired_button = tk.Button(
            button_frame, text="Mark as Repaired", command=self.mark_as_repaired, bg="lightcoral", fg="white"
        )
        self.mark_repaired_button.pack(side=tk.LEFT, padx=5)




        # Train Faults Treeview (Excel-like format)
        self.treeview_frame = tk.Frame(root)
        self.treeview_frame.pack(pady=10)
        
        self.treeview = ttk.Treeview(self.treeview_frame, columns=("Fault", "Description", "Repair Time (hrs)", "Severity"), show="headings")
        self.treeview.heading("Fault", text="Fault")
        self.treeview.heading("Description", text="Description")
        self.treeview.heading("Repair Time (hrs)", text="Repair Time (hrs)")
        self.treeview.heading("Severity", text="Severity")
        self.treeview.pack()

        self.total_repair_time_label = tk.Label(root, text="Total Repair Time: 0 hours")
        self.total_repair_time_label.pack(pady=5)

        # Initialize with example trains
        self.initialize_example_trains()

    def add_train(self):
        train_number = self.train_number_entry.get()
        if train_number:
            new_train = HighSpeedTrain(train_number)
            self.trains.append(new_train)
            self.refresh_train_list()
            self.train_number_entry.delete(0, tk.END)
        else:
            messagebox.showerror("Input Error", "Train number cannot be empty!")

    def show_fault_selection(self):
        selected_index = self.train_listbox.curselection()
        if not selected_index:
            messagebox.showerror("Selection Error", "Please select a train first!")
            return
        
        train = self.trains[selected_index[0]]

        fault_classes = [
            PassengerInfoFault, FireDetectionFault, ToiletSystemFault,
            LightingFault, BogieFault, DoorFault, TCMSCommunicationFault, AirConditioningFault,
            WheelsetFault, BrakeSystemFault, ElectricalFault, FuelSystemFault, EngineFault,
            TransmissionFault, CoolingSystemFault, HydraulicSystemFault, SuspensionFault,
            SignalSystemFault, BatteryFault
        ]

        fault_window = Toplevel(self.root)
        fault_window.title("Select Faults")
        fault_vars = []

        def add_selected_faults():
            selected_faults = [
                fault_class() for fault_var, fault_class in zip(fault_vars, fault_classes)
                if fault_var.get()
            ]
            for fault in selected_faults:
                train.add_fault(fault)
            self.refresh_train_list()
            fault_window.destroy()

        for fault_class in fault_classes:
            fault_var = IntVar()
            fault_vars.append(fault_var)
            Checkbutton(
                fault_window, text=fault_class()._name, variable=fault_var
            ).pack(anchor="w")

        tk.Button(fault_window, text="Add Selected Faults", command=add_selected_faults).pack()

    def view_details(self):
        selected_index = self.train_listbox.curselection()
        if selected_index:
            train = self.trains[selected_index[0]]
            self.treeview.delete(*self.treeview.get_children())
            total_repair_time = 0

            for fault in train.get_faults():
                repair_time = fault.calculate_repair_time()
                total_repair_time += repair_time
                self.treeview.insert("", "end", values=(
                    fault._name, fault._description, f"{repair_time:.2f}", fault._severity
                ))

            self.total_repair_time_label.config(text=f"Total Repair Time: {total_repair_time:.2f} hours")
        else:
            messagebox.showerror("Selection Error", "Please select a train first!")
        
        

    def mark_as_repaired(self):
        selected_index = self.train_listbox.curselection()
        if selected_index:
            train = self.trains[selected_index[0]]
            train.mark_as_repaired()
            self.refresh_train_list()
            messagebox.showinfo("Success", f"Train {train._train_number} has been marked as repaired!")
        else:
            messagebox.showerror("Selection Error", "Please select a train first!")
    

    def refresh_train_list(self):
        self.train_listbox.delete(0, tk.END)
        for train in self.trains:
            self.train_listbox.insert(tk.END, f"{train._train_number} ({train.get_train_status()})")

    def initialize_example_trains(self):
        example_train1 = HighSpeedTrain("E44.010")
        example_train1.add_fault(PassengerInfoFault())
        example_train1.add_fault(LightingFault())
        self.trains.append(example_train1)

        example_train2 = HighSpeedTrain("E68.004")
        example_train2.add_fault(FireDetectionFault())
        example_train2.add_fault(BrakeSystemFault())
        self.trains.append(example_train2)
        example_train2.mark_as_repaired()
        

        example_train3 = HighSpeedTrain("E80.000")
        example_train3.add_fault(DoorFault())
        example_train3.add_fault(AirConditioningFault())
        self.trains.append(example_train3)

        example_train4 = HighSpeedTrain("E44.005")
        example_train4.add_fault(TCMSCommunicationFault())
        example_train4.add_fault(BogieFault())
        self.trains.append(example_train4)

        example_train5 = HighSpeedTrain("E68.001")
        example_train5.add_fault(FireDetectionFault())
        example_train5.add_fault(PassengerInfoFault())
        self.trains.append(example_train5)
        example_train5.mark_as_repaired()
       

        example_train6 = HighSpeedTrain("E80.001")
        example_train6.add_fault(LightingFault())
        example_train6.add_fault(ToiletSystemFault())
        self.trains.append(example_train6)
        example_train6.mark_as_repaired()
       

        example_train7 = HighSpeedTrain("E44.002")
        example_train7.add_fault(DoorFault())
        example_train7.add_fault(AirConditioningFault())
        self.trains.append(example_train7)

        example_train8 = HighSpeedTrain("E68.007")
        example_train8.add_fault(BogieFault())
        example_train8.add_fault(TCMSCommunicationFault())
        self.trains.append(example_train8)

        example_train9 = HighSpeedTrain("E80.008")
        example_train9.add_fault(PassengerInfoFault())
        example_train9.add_fault(LightingFault())
        self.trains.append(example_train9)

        example_train10 = HighSpeedTrain("E44.033")
        example_train10.add_fault(FireDetectionFault())
        example_train10.add_fault(BrakeSystemFault())
        example_train10.add_fault(PassengerInfoFault())
        example_train10.add_fault(BogieFault())
        example_train10.add_fault(DoorFault())
        example_train10.add_fault(ToiletSystemFault())
        self.trains.append(example_train10)


        self.refresh_train_list()


# --- Run the GUI Application ---
if __name__ == "__main__":
    root = tk.Tk()
    app = MaintenanceApp(root)
    root.mainloop()
