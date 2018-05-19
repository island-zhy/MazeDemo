#include "Entity.h"


Entity::Entity() :m_body(nullptr), mTexSRV(nullptr){
	//���ò�������
	mMat.Ambient = XMFLOAT4(0.48f, 0.55f, 0.46f, 1.0f);
	mMat.Diffuse = XMFLOAT4(0.48f, 0.55f, 0.46f, 1.0f);
	mMat.Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);
}


Entity::~Entity()
{
	btRelease();
}

void Entity::initbtBody(const btRigidBody::btRigidBodyConstructionInfo& constructionInfor, btDiscreteDynamicsWorld * world) {
	//���� ��������
	m_body = new btRigidBody(constructionInfor);
	//�����û�ָ��
	m_body->setUserPointer(this);
	//���������� ���ӵ� ��������
	world->addRigidBody(m_body);
}

void Entity::draw(ID3D11DeviceContext* d3dImmediateContext, CXMMATRIX view, CXMMATRIX proj, int passIndex) {
	XMMATRIX rotation = XMLoadFloat4x4(&m_rotation);
	XMMATRIX world = XMMatrixMultiply(rotation,XMMatrixTranslation(m_position.x, m_position.y, m_position.z));
	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
	XMMATRIX worldViewProj = world * view * proj;

	Effects::BasicFX->SetWorld(world);
	Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::BasicFX->SetWorldViewProj(worldViewProj);
	Effects::BasicFX->SetTexTransform(XMMatrixIdentity());
	Effects::BasicFX->SetMaterial(mMat);
	if(mTexSRV)Effects::BasicFX->SetDiffuseMap(mTexSRV);

	ID3DX11EffectTechnique* activeTexTech = Effects::BasicFX->Light1TexTech;
	activeTexTech->GetPassByIndex(passIndex)->Apply(0, d3dImmediateContext);

	d3dImmediateContext->DrawIndexed(mIndexCount, mIndexOffset, mVertexOffset);
}

void Entity::update(float dt) {

}

void Entity::btRelease() {
	//if (m_body) {
	//	delete m_body;
	//	//TODO
	//	//		m_body->setFlags();
	//	m_body = nullptr;
	//}
}