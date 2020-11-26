package com.example;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import java.util.Optional;

@Path("/demo")
@Produces(MediaType.APPLICATION_JSON)
public class DemoResource
{
	private final String message;

	public DemoResource(String message)
	{
		this.message = message;
	}

	@GET
	public Message sendMessage(@QueryParam("text") Optional<String> text)
	{
		return new Message(message +  text.orElse("-"));
	}
}
