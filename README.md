# Dry Cleaning & Alterations Order Management System
## Overview

This project is based on the Qt framework using C++ to create a desktop application that was designed to manage customer orders for a dry cleaning business that also provides alteration services. 
It provides a full workflow for taking orders, processing, pickup tracking, pricing, taxation, and record persistence through a custom file-based storage system. It was built to support real-world retail dry-cleaning operations, including multi-service orders, pricing structures, and customer management.

---

## Features

### Customer Management

* Create and manage customer records
* Store customer contact information and order history
* Link customers to their orders
* Persistent storage of customer data

### Order Management

* Create, edit, and track orders
* Support for multiple service categories:

  * Laundry
  * Dry Cleaning
  * Alterations
* Track:

  * Order Information and Customer IDs
  * Number of pieces
  * Rack location
  * Drop-off and pickup dates
  * Payment status
  * Deposit information
  * Discounts and tax

### Pricing System

* Allows for dynamic pricing
* Service-specific pricing tables
* Supports multiple items per service category

### Tax & Financial Tracking

* Tracks taxable amounts per order
* Calculates tax and final cost
* Supports discount handling and recalculations
* Ability to generate reports for taxed orders within date ranges

### Data Persistence

* Custom file-based storage using `.txt` files
* Stores:

  * Orders
  * Customers
  * Pricing tables
  * Temporary order states
* Logging system for critical operations and errors
* Versioned data handling for file format changes

### Graphical User Interface (Qt)

Built using Qt Widgets (C++):

* Multi-page interface (drop-off, pickup, editing)
* Dynamic UI components and form layouts
* Hover and interactive UI elements
* Dialog confirmations and validation prompts

---

## Tech Stack

* **Language:** C++17+
* **Framework:** Qt (Widgets)
* **IDE:** Qt Creator
* **Architecture:** Object-oriented with modular file and UI separation
* **Storage:** Custom structured text files
* **Logging:** Internal logging system

---

## Project Structure (Conceptual)

```
/src
 ├── main.cpp
 ├── mainwindow.*                # Main UI controller
 ├── file.*                      # File I/O and persistence layer
 ├── order.*                     # Order class and logic
 ├── customer.*                  # Customer class
 ├── services/                   # Laundry, dry clean, alterations structures
 ├── date/                       # Custom date/time handling
 └── ui/                         # Qt Designer UI files
```

---

## Key Design Concepts

### Object-Oriented Architecture

The application separates responsibilities across multiple classes:

* `order` handles order-specific data and calculations
* `customer` manages customer records
* `File` manages persistent storage and logging
* UI logic is separated from business logic where possible

### File-Based Persistence

Instead of using a database, the application uses structured text files for:

* Simplicity
* Portability
* Transparency of stored data

A migration strategy is used when file formats evolve.

### Use of Modern C++

The project uses:

* `std::vector`
* `std::tuple`
* `std::optional`
* Strong encapsulation and getters/setters
* Structured data parsing and serialization

---

## Example Use Cases

* Creating a new order with multiple services
* Applying discounts and tax calculations
* Tracking pickup and payment status
* Searching and aggregating orders by date
* Generating tax-related reports
* Persisting and reloading all data between sessions

---

## Building & Running

### Requirements

* Qt 6.x (or compatible Qt 5.x version)
* C++17 compatible compiler
* Qt Creator recommended

### Build Steps

1. Open project in Qt Creator
2. Configure kit (Desktop Qt)
3. Build project
4. Run application

---

## Future Improvements

* Database backend (SQLite or PostgreSQL)
* Reporting and analytics dashboard
* Receipt printing integration
* Cloud backup or sync
* Automated testing suite

---



