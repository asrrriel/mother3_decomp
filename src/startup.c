void main();

//dumb BS
//original addr: $080000c0
void _start(void) __attribute__((section(".text.startup"),naked, used));
void _start() 
{
	while(1){
		main();
	}
}