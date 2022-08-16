## Threading & Events

This is a very simple app that takes in CLI input from a thread and prints out on another. It can handle two 3 commands.

* login <user> <password>
* register <user> <password>
* quit

Example

            $ make; ./events

            GUI thread >> Please enter your command.
            login khalil 1234  
            GUI Thread >> pushing to login with arguments -> khalil 1234
            GUI thread >> Please enter your command.
            EventLoopThread >> logging in user: 'khalil'  with password: '1234'


The `SkypeGUI` loops in a thread waiting for a user input. In this example we are blocking the loop with `std::get_line` whoever in a real GUI this would be a running
loop. Once event is detected the GUI pushes an event to `ThreadSafeQueue`.

`EventLoop` is running on another thread constantly checking `ThreadSafeQueue` for new events. Once an `Event` is available it will check the `EventType` and
delegate to an `EventHandler`.

Note that `ThreadSafequeue` handles the locks in its internal implementation so both the `SkypeGUI` thread and the `EventLoop` thread can access it safely.

## Still needs to do

In most cases we need to return some information back to the GUI. Let's discuss the best way.


