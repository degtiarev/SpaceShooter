
    varying vec2 texCoord;
	uniform sampler2D color;
	void main(){

	gl_FragColor = texture2D(color,texCoord.xy)*0.5;
    
	}