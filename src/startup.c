void main();

//dumb BS
void _start(void) __attribute__((section(".text.startup"),naked, used));
void _start() 
{
	while(1){
		main();
	}
}