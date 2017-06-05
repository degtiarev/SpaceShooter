#include "ParticlesEngineClass.h"



ParticlesEngineClass::ParticlesEngineClass(GLuint textureName)
{
	textureName_ = textureName;
}


ParticlesEngineClass::~ParticlesEngineClass()
{
}

void ParticlesEngineClass::privateInit()
{
	//particle init
	for (loop = 0; loop < MAX_PARTICLES; loop++)				// Initials All The Textures
	{

		particlesArray_[loop].active = true;										// Make All The Particles Active
		particlesArray_[loop].life = 1.0f;											// Give All The Particles Full Life
		particlesArray_[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;		// Random Fade Speed

		particlesArray_[loop].r = colors[loop*(12 / MAX_PARTICLES)][0];			// Select Red Rainbow Color
		particlesArray_[loop].g = colors[loop*(12 / MAX_PARTICLES)][1];			// Select Red Rainbow Color
		particlesArray_[loop].b = colors[loop*(12 / MAX_PARTICLES)][2];			// Select Red Rainbow Color

		particlesArray_[loop].xi = float((rand() % 50) - 25.0f)*10.0f;				// Random Speed On X Axis
		particlesArray_[loop].yi = float((rand() % 50) - 25.0f)*10.0f;				// Random Speed On Y Axis
		particlesArray_[loop].zi = 300 + float((rand() % 60) - 30.0f);		// Random Speed On Z Axis

	}

}

void ParticlesEngineClass::privateRender()
{
	glShadeModel(GL_SMOOTH);								// Enable Smooth Shading
	glClearDepth(1.0f);										// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);								// Disable Depth Testing
	glEnable(GL_BLEND);										// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);						// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);								// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D, textureName_);					// Select Our Texture

	for (loop = 0; loop < MAX_PARTICLES; loop++)					// Loop Through All The Particles
	{

		if (particlesArray_[loop].active) {						// If The Particle Is Active

			float x = particlesArray_[loop].x;						// Grab Our Particle X Position
			float y = particlesArray_[loop].y;						// Grab Our Particle Y Position
			float z = particlesArray_[loop].z;				// Particle Z Pos + Zoom

															// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(particlesArray_[loop].r, particlesArray_[loop].g, particlesArray_[loop].b, particlesArray_[loop].life);

			glBegin(GL_TRIANGLE_STRIP);								// Build Quad From A Triangle Strip
			glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z);	// Top Right
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z);	// Top Left
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z);	// Bottom Right
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z);	// Bottom Left
			glEnd();												// Done Building Triangle Strip

			particlesArray_[loop].x += particlesArray_[loop].xi / (2.0f * 5000);	// Move On The X Axis By X Speed
			particlesArray_[loop].y += particlesArray_[loop].yi / (2.0f * 5000);	// Move On The Y Axis By Y Speed
			particlesArray_[loop].z += particlesArray_[loop].zi / (2.0f * 5000);	// Move On The Z Axis By Z Speed

																					//Pull direction
			particlesArray_[loop].yi += particlesArray_[loop].yg;				// Take Pull On Y Axis Into Account

			particlesArray_[loop].life -= particlesArray_[loop].fade;			// Reduce Particles Life By 'Fade'

																				//Respawn the particles
			if (particlesArray_[loop].life < 0.0f)											// If Particle Is Burned Out
			{
				particlesArray_[loop].life = 1.0f;											// Give It New Life
				particlesArray_[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;		// Random Fade Speed
				particlesArray_[loop].x = 0.0f;											// Center On X Axis
				particlesArray_[loop].y = 0.0f;											// Center On Y Axis
				particlesArray_[loop].z = 0.0f;											// Center On Z Axis

																						//Direction
				particlesArray_[loop].zi = 300 + float((rand() % 60) - 30.0f);				// Z Axis Speed And Direction

				particlesArray_[loop].r = colors[0][0];			// Select Red From Color Table
				particlesArray_[loop].g = colors[0][1];			// Select Green From Color Table
				particlesArray_[loop].b = colors[0][2];			// Select Blue From Color Table
			}
		}
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

}

void ParticlesEngineClass::privateUpdate()
{
}
