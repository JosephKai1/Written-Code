import java.util.ArrayList;
//816034711

public class chatBotPlatform
{      
    public ArrayList<chatBot> bots;
    public chatBotPlatform()
    {
        bots= new ArrayList<chatBot>(7);
    }
    
    public boolean addChatBot(int LLMCode)
    {
        chatBot chatBot = new chatBot();
        if(chatBot.limitReached() == false)
        {
            bots.add(new chatBot(LLMCode));
            return true;
        }
        
        else
        {
            return false;
        }
    }
    
    public String getChatBotList()
    {
        String returnString = ("Your ChatBots\n");
        chatBot chatBot = new chatBot();
        
        for(chatBot x : bots)
        {
            int index = bots.indexOf(x);
            String chatBotInfo = x.toString();
            returnString += ("Bot Number: " + index + " ");
            returnString += chatBotInfo + "\n";
        }
        
        returnString += ("Number Messages Used: " 
                        + chatBot.getTotalNumResponsesGenerated());
        
        returnString += ("\nNumber Messages Remaining: " 
                        + chatBot.getTotalNumMessagesRemaining());
        returnString += ("\n--------------------");
        return returnString;
    } 
    
    public String interactWithBot(int botNumber, String message)
    {
        String returnString= "";
        chatBot chatBot = new chatBot();
        if(botNumber > 6 || botNumber < 0)
        {
            returnString = ("Incorrect BotNumber(" 
                            + botNumber + ")Selected. Try again");
        }
        
        else
        {
            chatBot = bots.get(botNumber);
            returnString += chatBot.prompt(message);
        }
        return returnString;
    }
    
    
}
