#include "libchapter3_private.h"
#include "Lights.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace
{
}

CAbstractLightSource::CAbstractLightSource(unsigned index)
    : m_index(index)
{
}

CAbstractLightSource::~CAbstractLightSource()
{
}

glm::vec4 CAbstractLightSource::GetUniformPosition() const
{
    return m_uniformPosition;
}

glm::vec4 CAbstractLightSource::GetAmbient() const
{
    return m_ambient;
}

glm::vec4 CAbstractLightSource::GetDiffuse() const
{
    return m_diffuse;
}

glm::vec4 CAbstractLightSource::GetSpecular() const
{
    return m_specular;
}

void CAbstractLightSource::SetAmbient(const glm::vec4 &color)
{
    m_ambient = color;
}

void CAbstractLightSource::SetDiffuse(const glm::vec4 &color)
{
    m_diffuse = color;
}

void CAbstractLightSource::SetSpecular(const glm::vec4 &color)
{
    m_specular = color;
}

void CAbstractLightSource::SetUniformPosition(const glm::vec4 &position)
{
    m_uniformPosition = position;
}

void CAbstractLightSource::SetupImpl() const
{
    // Включаем источник света с заданным индексом.
    // Источник действует только когда включен режим GL_LIGHTING!
    glEnable(GLenum(m_index));
    glLightfv(m_index, GL_AMBIENT, glm::value_ptr(m_ambient));
    glLightfv(m_index, GL_DIFFUSE, glm::value_ptr(m_diffuse));
    glLightfv(m_index, GL_SPECULAR, glm::value_ptr(m_specular));
}

unsigned CAbstractLightSource::GetIndex() const
{
    return m_index;
}

CDirectedLightSource::CDirectedLightSource(unsigned index)
    : CAbstractLightSource(index)
{
    SetUniformPosition({0, 0, 0, 0});
}

glm::vec3 CDirectedLightSource::GetDirection() const
{
    return glm::vec3(GetUniformPosition());
}

void CDirectedLightSource::SetDirection(const glm::vec3 &value)
{
    SetUniformPosition({value.x, value.y, value.z, 0.f});
}

void CDirectedLightSource::Setup() const
{
    SetupImpl();
    // Если GL_POSITION установить как (x, y, z, 0), т.е. как вектор
    // в однородных координатах, источник света будет направленным.
    glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(GetUniformPosition()));
}

CPositionLightSource::CPositionLightSource(unsigned index)
    : CAbstractLightSource(index)
{
    SetUniformPosition({0, 0, 0, 1});
}

glm::vec3 CPositionLightSource::GetPosition() const
{
    return glm::vec3(GetUniformPosition());
}

void CPositionLightSource::SetPosition(const glm::vec3 &value)
{
    SetUniformPosition({value.x, value.y, value.z, 1.f});
}

void CPositionLightSource::Setup() const
{
    SetupImpl();
    // Если GL_POSITION установить как (x, y, z, 1), т.е. как точку
    // в однородных координатах, источник света будет точечным.
    glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(GetUniformPosition()));
}

CSpotlightLightSource::CSpotlightLightSource(unsigned index)
    : CAbstractLightSource(index)
{

}

glm::vec3 CSpotlightLightSource::GetPosition() const
{
	return m_position;
	//return glm::vec3(GetUniformPosition());
}

void CSpotlightLightSource::SetPosition(const glm::vec3 &value)
{
	m_position = value;
	//SetUniformPosition({ value.x, value.y, value.z, 1.f });
}

glm::vec3 CSpotlightLightSource::GetDirection() const
{
	return m_direction;
}

void CSpotlightLightSource::SetDirection(const glm::vec3 &value)
{
	m_direction = value;
}

void CSpotlightLightSource::SetAngle(float angle)
{
	m_angle = angle;
}

float CSpotlightLightSource::GetAngle() const
{
	return m_angle;
}

void CSpotlightLightSource::Setup() const
{
	//SetupImpl();
	//glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(GetUniformPosition()));
	
	//GLfloat light4_diffuse[] = { 0.4, 0.7, 0.2 };
	//GLfloat light4_position[] = { 0.0, 0.0, 1.0, 1.0 };
	//GLfloat light4_spot_direction[] = { 0.0, 0.0, -1.0 };
	//glEnable(GetIndex());
	glEnable(GLenum(m_index));
	//glLightfv(GetIndex(), GL_DIFFUSE, glm::value_ptr(GetDiffuse()));

	const glm::vec4 pos(GetPosition(), 0.f);
	const glm::vec4 direction(GetDirection(), 1.f);

	glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(pos));
	glLightf(GetIndex(), GL_SPOT_CUTOFF, m_angle);
	glLightfv(GetIndex(), GL_SPOT_DIRECTION, glm::value_ptr(direction));

	glLightfv(m_index, GL_AMBIENT, glm::value_ptr(m_ambient));
	glLightfv(m_index, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glLightfv(m_index, GL_SPECULAR, glm::value_ptr(m_specular));

	/*glLightf(GetIndex(), GL_SPOT_EXPONENT, 15.f);

	glLightf(GetIndex(), GL_CONSTANT_ATTENUATION, 0.8f);
	glLightf(GetIndex(), GL_LINEAR_ATTENUATION, 0.3f);
	glLightf(GetIndex(), GL_QUADRATIC_ATTENUATION, 0.3f);*/
}


void CPhongModelMaterial::Setup() const
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(m_emission));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specular));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}

glm::vec4 CPhongModelMaterial::GetEmission() const
{
    return m_emission;
}

void CPhongModelMaterial::SetEmission(const glm::vec4 &emission)
{
    m_emission = emission;
}

glm::vec4 CPhongModelMaterial::GetAmbient() const
{
    return m_ambient;
}

void CPhongModelMaterial::SetAmbient(const glm::vec4 &ambient)
{
    m_ambient = ambient;
}

glm::vec4 CPhongModelMaterial::GetDiffuse() const
{
    return m_diffuse;
}

void CPhongModelMaterial::SetDiffuse(const glm::vec4 &diffuse)
{
    m_diffuse = diffuse;
}

glm::vec4 CPhongModelMaterial::GetSpecular() const
{
    return m_specular;
}

void CPhongModelMaterial::SetSpecular(const glm::vec4 &specular)
{
    m_specular = specular;
}

float CPhongModelMaterial::GetShininess() const
{
    return m_shininess;
}

void CPhongModelMaterial::SetShininess(float shininess)
{
    m_shininess = shininess;
}
