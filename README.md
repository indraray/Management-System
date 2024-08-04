# Event Management System

This application is a C++ based Event Management System which allows both Participants and Admins to interact with various events such as Competitions, Programs, and Sessions. The system supports user registration, event creation, editing, deletion, and more.

## Functionalities

### General
- **User Management**:
  - Add, view, and edit user profiles
  - Save and load user data from files

- **Event Management**:
  - Add, view, edit, and delete events
  - Save and load event data from files

### User Types
1. **Participant**:
   - Register for events
   - View registered events
   - Cancel event registrations

2. **Admin**:
   - Manage events (create, edit, delete)
   - View all events

## Concepts
- **Inheritance**: Used for different user types and event types.
- **Polymorphism**: Virtual functions to allow specific behavior for different derived classes.
- **File I/O**: Save and load user and event data to/from files.
- **Encapsulation**: Keeping the data and functions within classes to ensure modularity and security.

## Classes
- `User`: Base class for user-related information and operations.
  - `Participant`: Derived from `User`, handles event registration.
  - `Admin`: Derived from `User`, handles event management.
  
- `Event`: Base class for event-related information and operations.
  - `Competition`, `Program`, `Session`: Derived from `Event`, handle specific event details.

- `EventManager`: Manages the collection of users and events, facilitates saving and loading data.

## Usage
1. **Admin Dashboard**:
   - View all events
   - Edit event details
   - Add new events
   - Delete events
   - Edit profile

2. **Participant Dashboard**:
   - View all events
   - Register for events
   - View registered events
   - Edit profile
   - Cancel registration
