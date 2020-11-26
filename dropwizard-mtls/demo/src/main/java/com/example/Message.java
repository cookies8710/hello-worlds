package com.example;

import com.fasterxml.jackson.annotation.JsonProperty;

public class Message {
	private String content;

	public Message() {}

	public Message(String content) {
		this.content = content;
	}

	@JsonProperty
	public String getContent() {
		return content;
	}
}

