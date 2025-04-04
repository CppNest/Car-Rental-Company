# Car-Rental-Company

Car-Rental-Company is a project designed to demonstrate the fundamentals of **C++** and **Qt Framework**. This application provides a user-friendly interface for managing car rentals, showcasing modern GUI design and functionality.

---

## 🚀 Features

- **Dynamic Car Management**: Add, search, and filter cars based on various criteria.
- **Reservation System**: Reserve cars with detailed cost calculations.
- **Modern UI**: Clean and professional design using Qt Widgets.
- **Multi-Window Navigation**: Includes windows for Menu, Main, Reservations, and All Reservations.

---

## 📂 Project Structure

Car-Rental-Company/
│
├── Car.cpp / Car.h # Base class for all car types
├── ElectricCar.cpp / ElectricCar.h # Electric car implementation  
├── PassengerCar.cpp / PassengerCar.h # Passenger car implementation  
├── SportCar.cpp / SportCar.h # Sport car implementation  
├── TruckCar.cpp / TruckCar.h # Truck car implementation  
├── main.cpp # Application entry point  
├── mainwindow.cpp / mainwindow.h / mainwindow.ui # Main window for car browsing  
├── menuwindow.cpp / menuwindow.h / menuwindow.ui # Menu window  
├── reservationwindow.cpp / reservationwindow.h / reservationwindow.ui # Reservation window  
├── allreservationswindow.cpp / allreservationswindow.h / allreservationswindow.ui # All reservations window
│
├── build/  
│ ├── data.txt # Stores available cars  
│ ├── reservations.txt # Stores reservation details  
│ ├── icons/ # Icons for the UI  
│ └── cars/ # Images of cars  
│
├── LICENSE # License file  
├── README.md # Project documentation  
└── CarRentalCompany.pro # Qt project file

---

## 🛠️ Technologies Used

- **C++**: For core application logic.
- **Qt Framework**: For GUI design and functionality.
- **QFile and QTextStream**: For file handling.
- **QMessageBox**: For user notifications.
- **QPixmap**: For image handling.

---

## 🌟 Key Functionalities

1. **Menu Window**:

   - Navigation to different sections of the application.

2. **Main Window**:

   - Search and filter cars by name, type, seats, and price.
   - Paginated car browsing.

3. **Reservation Window**:

   - Display car details and calculate total cost based on rental days.
   - Save reservations to a file.

4. **All Reservations Window**:
   - View all reservations in a table format.
   - Cancel reservations and restore cars to availability.

---

## ⚙️ Installation and Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/Car-Rental-Company.git
   ```
2. Open CarRentalComapny.pro in Qt Creator.
3. Build and run the project.

---

## 🤝 Contributing

Contributions are welcome! If you have suggestions or improvements, feel free to fork the repository and submit a pull request.

---

## 📜 License

This project is under the MIT License - see the [LICENSE](./LICENSE) file for details.
