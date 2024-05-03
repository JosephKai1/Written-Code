
//816034711

public class chatBot
{
    private String chatBotName;
    private int numResponsesGenerated;
    private static final int messageLimit;
    private static int messageNumber;
    
    static{
        messageLimit = 10;
        messageNumber = 0;
    }
    
    //Constructor no args
    public chatBot()
    {
        chatBotGenerator chatBotGen1 = new chatBotGenerator();
        this.chatBotName = chatBotGen1.generateChatBotLLM(0);
        this.numResponsesGenerated = 0;
    }
    
    //Constructor one arg
    public chatBot(int LLMCode)
    {
        chatBotGenerator chatBotGen2 = new chatBotGenerator();
        this.chatBotName = chatBotGen2.generateChatBotLLM(LLMCode);
        this.numResponsesGenerated = 0;
    }
    
    //Accessors
    public String getChatBotName() {return chatBotName;}
    
    public int getNumResponsesGenerated()
    {
        return this.numResponsesGenerated;
    }
    
    public static int getTotalNumResponsesGenerated()
    {
        return messageNumber;
    }
    
    public int getTotalNumMessagesRemaining()
    {
        return (messageLimit - messageNumber);
    }
    
    public static boolean limitReached() 
    {
        boolean limit;
        limit = false;
        
        if(messageNumber == 10)
        {
            limit = true;
        }
        return limit;
    }
    
    private String generateResponse()
    {
        String response = "";
        response += ("(Message #" + (messageNumber + 1) + ") ");
        response += ("Response from " + chatBotName + " \t>>generatedTextHere"); 
        messageNumber = messageNumber + 1;
        this.numResponsesGenerated += 1;
        return response;
    }
    
    public String prompt(String requestMessage)
    {
        String response = "";
        if(messageNumber < 10)
        {
            response = generateResponse();
        }
        else
        {
            response = "Daily Limit reached. Wait 24 hours to resume chatbot usage";
        }
        return response;
    }
    
    public String toString()
    {
        return("ChatBot Name: " + chatBotName + "\t" +
                " Number Messages Used: " + numResponsesGenerated);
    }
}