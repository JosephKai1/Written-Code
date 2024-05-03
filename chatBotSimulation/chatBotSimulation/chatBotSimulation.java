//816034711
import java.util.Random;

public class chatBotSimulation
{
    public static void main()
    {        
        System.out.println("Hello World");
        System.out.println("--------------------");
        chatBotPlatform chatBotPlatform = new chatBotPlatform();
    
        for(int i = 0; i < 7; i++)
        {
            boolean added = chatBotPlatform.addChatBot(i);
            if(!added)
            {
                System.out.println("Error in adding chatBot");
                break;
            }
        }
        System.out.println(chatBotPlatform.getChatBotList());
        System.out.println();
        
        for(int i=1; i<=15; i++)
        {        
            Random rand = new Random();
            int rand1 = rand.nextInt(8);
            System.out.println(chatBotPlatform.interactWithBot(rand1, "Hello World"));
        }
        System.out.println();
        System.out.println(chatBotPlatform.getChatBotList());
    }
}