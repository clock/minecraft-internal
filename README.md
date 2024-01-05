# Minecraft Lunar Client 1.8.9 Injection Client

## Introduction

This project is an injection client for Minecraft's Lunar Client version 1.8.9. It was developed to maintain my coding skills and to explore the possibilities of modifying the Lunar Client.

## How It Works

The core of this project involves injecting a DLL into the game. The process includes:

1. **Accessing the JVM:** We start by accessing a VM thread from the JVM (Java Virtual Machine) running the game.
2. **Class Enumeration:** The next step involves looping through all game classes. We log their names, which is crucial since Lunar Client employs a custom class loader.
3. **Field and Method Access:** By doing this, we can access fields and methods from these classes, as well as interact with pre-existing objects within the game environment.

## Dependencies

The project relies on several key dependencies:

- **MinHook:** Used for trampoline hooking of networking functions, swap buffers, and wndproc.
- **OpenGL ImGui:** This is utilized for creating the user interface, specifically the menu.

## Project Structure

For a visual representation of the project structure, please refer to the following image:

[![Project Structure](https://github.com/clock/minecraft-backtrack/assets/29989334/e96fbdb4-2ebc-41e5-9202-31b31a5b3d58)](https://github.com/clock/minecraft-backtrack/assets/29989334/e96fbdb4-2ebc-41e5-9202-31b31a5b3d58)
